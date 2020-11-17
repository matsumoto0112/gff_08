// Fill out your copyright notice in the Description page of Project Settings.

#include "Boat.h"

#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/MyLogCategory.h"
#include "gff_08/utils/SpeedConverter.h"
#include "kismet/KismetSystemLibrary.h"

namespace {
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

//�@�̂̕ύX
void ABoat::ChangeBoat(int32 BoatID, int32 PlayerIndex) {
	// ID����p�����[�^���擾����
	if (!BoatDataAsset->Data.IsValidIndex(BoatID)) {
		UE_LOG(LogBoat, Error, TEXT("Boat parameter is not defined."));
		return;
	}

	this->PlayerIndex_ = PlayerIndex;

	//�p�����[�^��K�v�ȕϐ��ɑ�����Ă���
	const FBoatParameterRecord Parameter = BoatDataAsset->Data[BoatID];
	BoatMover->SetParameter(Parameter.MaxSpeed, Parameter.Acceleration, Parameter.Control);
	this->StaticMesh->SetStaticMesh(Parameter.BoatMesh);
	this->StaticMesh->SetMaterial(0, Parameter.Materials[PlayerIndex]);
	this->StaticMesh->SetMassOverrideInKg(NAME_None, Parameter.Mass);
}

//���[�X�̏���
void ABoat::RaceReady(ACheckPoint* StartCheckPoint) {
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, TEXT("RaceReady Called!"));
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

void ABoat::PushMovementValue() {
	const FInputInfo InputInfo = IDriver::Execute_CurrentInputInfo(Driver.GetObject());
	PrevMotorValues.Emplace(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);

	if (PrevMotorValues.Num() > NEED_MOTOR_VALUE_NUM) {
		PrevMotorValues.RemoveAt(0);
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
			LeftValue = 0.0f;
			RightValue = 0.0f;
			break;
			//���̑�
		default:
			UE_LOG(LogTemp, Error, TEXT("Unconfirmed enum EBoatMovableType encounter."));
			break;
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
	// const float Dot = ForwardVector.CosineAngle2D(To);
	const float DotProduct = FVector::DotProduct(To, ForwardVector);
	const float Dot = FMath::Acos(DotProduct);
	const float Deg = FMath::RadiansToDegrees(Dot);
	//GEngine->AddOnScreenDebugMessage(
	//	-1, 0.0f, FColor::Red, FString::Format(TEXT("{0}: {1}"), {GetName(), FMath::RadiansToDegrees(Dot)}));
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

	//�����ɑ΂���p�����[�^�ݒ�
	MoveSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
	ScrewSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
