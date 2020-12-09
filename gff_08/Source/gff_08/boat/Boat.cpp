// Fill out your copyright notice in the Description page of Project Settings.

#include "Boat.h"

#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/MyLogCategory.h"
#include "gff_08/utils/SpeedConverter.h"
#include "kismet/GamePlayStatics.h"
#include "kismet/KismetSystemLibrary.h"

namespace {
static const FName DEFAULT_COLLISION_PROFILE_NAME = TEXT("Boat_Default");
static const FName FLASH_COLLISION_PROFILE_NAME = TEXT("Boat_Flash");

constexpr int32 NEED_MOTOR_VALUE_NUM = 5;
bool IsMaintaining(const TArray<TPair<float, float>>& MotorValues) {
	if (MotorValues.Num() < NEED_MOTOR_VALUE_NUM) {
		return false;
	}

	float Left_Min = MotorValues[0].Key;
	float Left_Max = MotorValues[0].Key;
	float Right_Min = MotorValues[0].Value;
	float Right_Max = MotorValues[0].Value;
	for (int32 i = 1; i < MotorValues.Num(); i++) {
		Left_Min = FMath::Min(Left_Min, MotorValues[i].Key);
		Left_Max = FMath::Max(Left_Max, MotorValues[i].Key);
		Right_Min = FMath::Min(Right_Min, MotorValues[i].Value);
		Right_Max = FMath::Max(Right_Max, MotorValues[i].Value);
	}

	return Left_Max - Left_Min < 0.01f && Right_Max - Right_Min < 0.01f;
}

constexpr int32 NEED_HISTORY_NUM = 15;

/**
 * �ő啜���͂𒴂�����]�����Ă��邩
 * X���Ɉ��̉�]�ʂ������Ă���ƁA�@�̂̕����͂𒴂���
 */
bool IsOverMaxRestoreForce(const TArray<float>& RotationXHistory) {
	if (RotationXHistory.Num() < NEED_HISTORY_NUM) {
		return false;
	}

	float Min = RotationXHistory[0];
	float Max = RotationXHistory[0];
	for (int32 i = 1; i < RotationXHistory.Num(); i++) {
		Min = FMath::Min(Min, RotationXHistory[i]);
		Max = FMath::Max(Max, RotationXHistory[i]);
	}

	//�����ł��Ȃ��Ɣ��f����臒l
	//�����l
	constexpr float THRESHOLD = 58.0f;
	return Min >= THRESHOLD;
}
}	 // namespace

// Sets default values
ABoat::ABoat() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�K�v�ȃR���|�[�l���g�̍쐬
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	BoatMover = CreateDefaultSubobject<UBoatMover>(TEXT("BoatMover"));
	this->AddOwnedComponent(BoatMover);

	LapCounter = CreateDefaultSubobject<ULapCounter>(TEXT("LapCounter"));
	this->AddOwnedComponent(LapCounter);

	VisualBoatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualBoatMesh"));
	VisualBoatMesh->SetupAttachment(RootComponent);

	SteerForceLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("SteerForceLocation"));
	SteerForceLocation->SetupAttachment(RootComponent);

	GenerateWaveLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("GenerateWaveLocation"));
	GenerateWaveLocation->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABoat::BeginPlay() {
	Super::BeginPlay();

	//�ŏ��͈ړ����Ȃ��ݒ�ɂ���
	MoveType = EBoatMovableType::NoMove;

	FBoatMoverInitStructure InitStructure;
	InitStructure.ParentPawn = this;
	InitStructure.BoatMesh = this->StaticMesh;
	InitStructure.GenerateWaveLocation = this->GenerateWaveLocation;
	InitStructure.SteerForceLocation = this->SteerForceLocation;
	InitStructure.VisualBoatMesh = this->VisualBoatMesh;
	BoatMover->Init(InitStructure);

	//�����I�u�W�F�N�g�̍쐬
	const UMyGameInstance* Instance = UMyGameInstance::GetInstance();
	USoundSystem* SoundSystem = Instance->GetSoundSystem();
	MoveSound = SoundSystem->PlaySoundWithAttachOwnerActor(ESoundResourceType::SE_BOAT_MOVE, this, false);
	ScrewSound = SoundSystem->PlaySoundWithAttachOwnerActor(ESoundResourceType::SE_BOAT_SCREW, this, false);
}

void ABoat::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	if (PrevMotorValueStockHandle.IsValid()) {
		GetWorld()->GetTimerManager().ClearTimer(PrevMotorValueStockHandle);
		PrevMotorValueStockHandle.Invalidate();
	}

	//�����̒�~
	MoveSound->Stop();
	ScrewSound->Stop();
}

//���[�X�̏���
void ABoat::RaceReady(ACheckPoint* StartCheckPoint) {
	//�ŏ��̃`�F�b�N�|�C���g��ݒ肷��
	NextCheckPoint = StartCheckPoint;
	//�����ړ�����悤�ݒ�
	MoveType = EBoatMovableType::StraightOnly;

	//���݂̃��[�^�[�̒l��ۑ����Ă����^�C�}�[�̐ݒ�
	GetWorld()->GetTimerManager().SetTimer(
		PrevMotorValueStockHandle, this, &ABoat::PushMovementValue, PrevMotorValueStockInterval, true);
}

//���[�X�̊J�n
void ABoat::RaceStart() {
	//�������玩�R�Ɉړ��ł���悤�ɂ���
	MoveType = EBoatMovableType::Default;
}

//�v���C���[�̃X�s�[�h���擾����
float ABoat::GetPlayerSpeed() const {
	// km/s�ɕϊ�����
	return USpeedConverter::ToSpeedKilometerPerHour(GetVelocity().Size());
}

void ABoat::SetRacerInfo(const FRacerInfo& InRacerInfo) {
	this->RacerInfo = InRacerInfo;
	// ID����p�����[�^���擾����
	if (!BoatDataAsset->Data.IsValidIndex(RacerInfo.BoatIndex)) {
		UE_LOG(LogBoat, Error, TEXT("Boat parameter is not defined."));
		return;
	}

	//�p�����[�^��K�v�ȕϐ��ɑ�����Ă���
	const FBoatParameterRecord Parameter = BoatDataAsset->Data[RacerInfo.BoatIndex];
	BoatMover->SetParameter(Parameter.MaxSpeed, Parameter.Acceleration, Parameter.Control);
	this->StaticMesh->SetStaticMesh(Parameter.BoatMesh);
	this->StaticMesh->SetMaterial(0, Parameter.Materials[RacerInfo.PlayerIndex]);
	this->StaticMesh->SetMassOverrideInKg(NAME_None, Parameter.Mass);

	this->StaticMesh->SetVisibility(false);

	this->VisualBoatMesh->SetStaticMesh(Parameter.BoatMesh);
	this->VisualBoatMesh->SetMaterial(0, Parameter.Materials[RacerInfo.PlayerIndex]);
	this->VisualBoatMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABoat::ReturnPrevCheckPoint() {
	ACheckPoint* PrevCheckPoint = NextCheckPoint->GetPrevPoint();
	SetActorLocationAndRotation(PrevCheckPoint->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f),
		PrevCheckPoint->GetActorRotation() + FRotator::MakeFromEuler(FVector(0, 0, -90.0f)));
	bFlasing = true;
	this->StaticMesh->SetCollisionProfileName(FLASH_COLLISION_PROFILE_NAME);
}

void ABoat::OnEnableAutoMode() {
	OnEventDispatcher.Broadcast();
}

void ABoat::PushMovementValue() {
	const FInputInfo InputInfo = IDriver::Execute_CurrentInputInfo(Driver.GetObject());
	PrevMotorValues.Emplace(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);

	if (PrevMotorValues.Num() > NEED_MOTOR_VALUE_NUM) {
		PrevMotorValues.RemoveAt(0);
	}

	RotationXHistory.Push(FMath::Abs(GetActorRotation().Euler().X));
	if (RotationXHistory.Num() > NEED_HISTORY_NUM) {
		RotationXHistory.RemoveAt(0);
	}
}

//�ړ��͂��v�Z����
void ABoat::CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const {
	const FInputInfo InputInfo = IDriver::Execute_CurrentInputInfo(Driver.GetObject());

	const float Coef = InputInfo.bBack ? -1.0f : 1.0f;

	const float MinValue = FMath::Min(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);
	const float MaxValue = FMath::Max(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);

	//�p�����ێ����Ă��鎞�Ԃ�������Β����ق�MaxValue�̒l�ɋ߂Â�
	const float MovementValue =
		FMath::Lerp(MinValue, MaxValue, FMath::Min(1.0f, PostureMaintainingTime / MaxInfluencePostureMaintainingTime));

	switch (MoveType) {
		case EBoatMovableType::Default:
			MoveValue = Coef * MovementValue;
			LeftValue = Coef * (InputInfo.LeftMotorValue - MinValue);
			RightValue = Coef * (InputInfo.RightMotorValue - MinValue);
			break;
			//�ړ��Ȃ�
		case EBoatMovableType::NoMove:
			MoveValue = 0.0f;
			LeftValue = 0.0f;
			RightValue = 0.0f;
			break;
			//���i�̂�
		case EBoatMovableType::StraightOnly:
			MoveValue = 0.8f;	 //�萔�ňړ�����
			MoveValue = 0.0f;
			LeftValue = 0.0f;
			RightValue = 0.0f;
			{
				FVector ForwardVector = StaticMesh->GetForwardVector() * 2000.0f;
				ForwardVector.Z = -980.0f;
				StaticMesh->SetPhysicsLinearVelocity(ForwardVector);
			}
			break;
			//���̑�
		default:
			UE_LOG(LogTemp, Error, TEXT("Unconfirmed enum EBoatMovableType encounter."));
			break;
	}
	if (bFlipInput) {
		std::swap(LeftValue, RightValue);
	}
}

//���Ε����Ɉړ�����
bool ABoat::IsReverseDriving() const {
	if (NextCheckPoint == nullptr) {
		return false;
	}
	//���ʂƂ̃x�N�g���Ŕ��肷��
	const FVector ForwardVector = GetActorForwardVector().GetSafeNormal2D();
	const FVector To = (NextCheckPoint->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
	const float DotProduct = FVector::DotProduct(To, ForwardVector);
	const float Dot = FMath::Acos(DotProduct);
	const float Deg = FMath::RadiansToDegrees(Dot);
	return Deg > 120.0f;
}

// Called every frame
void ABoat::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//�ړ��Ɏg�p����p�����[�^�̓h���C�o�[���v�Z����
	IDriver::Execute_UpdateInputInfo(Driver.GetObject());
	//�ړ��͌v�Z
	float MoveValue;
	float LeftValue;
	float RightValue;
	CalcMovementValues(MoveValue, LeftValue, RightValue);
	BoatMover->Move(MoveValue, LeftValue, RightValue);

	//�p�����ێ����Ă���Ƃ��Ɏ��Ԃ����Z���Ă���
	if (IsMaintaining(PrevMotorValues)) {
		PostureMaintainingTime += GetWorld()->GetDeltaSeconds();
	} else {
		PostureMaintainingTime = 0;
	}

	if (IsOverMaxRestoreForce(RotationXHistory)) {
		ReturnPrevCheckPoint();
		RotationXHistory.Empty();
	}

	if (bFlasing) {
		FlashTime += DeltaTime;

		const bool visibility = static_cast<int32>(FlashTime / 0.1f) % 2 == 0;
		this->VisualBoatMesh->SetVisibility(visibility);

		if (FlashTime >= 2.0f) {
			FlashTime = 0.0f;
			bFlasing = false;
			this->StaticMesh->SetCollisionProfileName(DEFAULT_COLLISION_PROFILE_NAME);
			this->VisualBoatMesh->SetVisibility(true);
		}
	}

	//�����ɑ΂���p�����[�^�ݒ�
	MoveSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
	ScrewSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
