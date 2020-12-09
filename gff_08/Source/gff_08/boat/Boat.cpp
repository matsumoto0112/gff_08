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
 * 最大復元力を超えた回転をしているか
 * X軸に一定の回転量を持っていると、機体の復元力を超える
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

	//復元できないと判断する閾値
	//実測値
	constexpr float THRESHOLD = 58.0f;
	return Min >= THRESHOLD;
}
}	 // namespace

// Sets default values
ABoat::ABoat() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//必要なコンポーネントの作成
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

	//最初は移動しない設定にする
	MoveType = EBoatMovableType::NoMove;

	FBoatMoverInitStructure InitStructure;
	InitStructure.ParentPawn = this;
	InitStructure.BoatMesh = this->StaticMesh;
	InitStructure.GenerateWaveLocation = this->GenerateWaveLocation;
	InitStructure.SteerForceLocation = this->SteerForceLocation;
	InitStructure.VisualBoatMesh = this->VisualBoatMesh;
	BoatMover->Init(InitStructure);

	//音源オブジェクトの作成
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

	//音源の停止
	MoveSound->Stop();
	ScrewSound->Stop();
}

//レースの準備
void ABoat::RaceReady(ACheckPoint* StartCheckPoint) {
	//最初のチェックポイントを設定する
	NextCheckPoint = StartCheckPoint;
	//直線移動するよう設定
	MoveType = EBoatMovableType::StraightOnly;

	//現在のモーターの値を保存していくタイマーの設定
	GetWorld()->GetTimerManager().SetTimer(
		PrevMotorValueStockHandle, this, &ABoat::PushMovementValue, PrevMotorValueStockInterval, true);
}

//レースの開始
void ABoat::RaceStart() {
	//ここから自由に移動できるようにする
	MoveType = EBoatMovableType::Default;
}

//プレイヤーのスピードを取得する
float ABoat::GetPlayerSpeed() const {
	// km/sに変換する
	return USpeedConverter::ToSpeedKilometerPerHour(GetVelocity().Size());
}

void ABoat::SetRacerInfo(const FRacerInfo& InRacerInfo) {
	this->RacerInfo = InRacerInfo;
	// IDからパラメータを取得する
	if (!BoatDataAsset->Data.IsValidIndex(RacerInfo.BoatIndex)) {
		UE_LOG(LogBoat, Error, TEXT("Boat parameter is not defined."));
		return;
	}

	//パラメータを必要な変数に代入していく
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

//移動力を計算する
void ABoat::CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const {
	const FInputInfo InputInfo = IDriver::Execute_CurrentInputInfo(Driver.GetObject());

	const float Coef = InputInfo.bBack ? -1.0f : 1.0f;

	const float MinValue = FMath::Min(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);
	const float MaxValue = FMath::Max(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);

	//姿勢を維持している時間が長ければ長いほどMaxValueの値に近づく
	const float MovementValue =
		FMath::Lerp(MinValue, MaxValue, FMath::Min(1.0f, PostureMaintainingTime / MaxInfluencePostureMaintainingTime));

	switch (MoveType) {
		case EBoatMovableType::Default:
			MoveValue = Coef * MovementValue;
			LeftValue = Coef * (InputInfo.LeftMotorValue - MinValue);
			RightValue = Coef * (InputInfo.RightMotorValue - MinValue);
			break;
			//移動なし
		case EBoatMovableType::NoMove:
			MoveValue = 0.0f;
			LeftValue = 0.0f;
			RightValue = 0.0f;
			break;
			//直進のみ
		case EBoatMovableType::StraightOnly:
			MoveValue = 0.8f;	 //定数で移動する
			MoveValue = 0.0f;
			LeftValue = 0.0f;
			RightValue = 0.0f;
			{
				FVector ForwardVector = StaticMesh->GetForwardVector() * 2000.0f;
				ForwardVector.Z = -980.0f;
				StaticMesh->SetPhysicsLinearVelocity(ForwardVector);
			}
			break;
			//その他
		default:
			UE_LOG(LogTemp, Error, TEXT("Unconfirmed enum EBoatMovableType encounter."));
			break;
	}
	if (bFlipInput) {
		std::swap(LeftValue, RightValue);
	}
}

//反対方向に移動中か
bool ABoat::IsReverseDriving() const {
	if (NextCheckPoint == nullptr) {
		return false;
	}
	//正面とのベクトルで判定する
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

	//移動に使用するパラメータはドライバーが計算する
	IDriver::Execute_UpdateInputInfo(Driver.GetObject());
	//移動力計算
	float MoveValue;
	float LeftValue;
	float RightValue;
	CalcMovementValues(MoveValue, LeftValue, RightValue);
	BoatMover->Move(MoveValue, LeftValue, RightValue);

	//姿勢を維持しているときに時間を加算していく
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

	//音源に対するパラメータ設定
	MoveSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
	ScrewSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
