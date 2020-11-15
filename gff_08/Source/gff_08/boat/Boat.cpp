// Fill out your copyright notice in the Description page of Project Settings.

#include "Boat.h"

#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/MyLogCategory.h"
#include "gff_08/utils/SpeedConverter.h"
#include "kismet/KismetSystemLibrary.h"

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
	BoatMover->Init(InitStructure);

	//音源オブジェクトの作成
	const UMyGameInstance* Instance = UMyGameInstance::GetInstance();
	USoundSystem* SoundSystem = Instance->GetSoundSystem();
	MoveSound = SoundSystem->PlaySoundWithAttachOwnerActor(ESoundResourceType::SE_BOAT_MOVE, this, false);
	ScrewSound = SoundSystem->PlaySoundWithAttachOwnerActor(ESoundResourceType::SE_BOAT_SCREW, this, false);
}

void ABoat::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	//音源の停止
	MoveSound->Stop();
	ScrewSound->Stop();
}

//機体の変更
void ABoat::ChangeBoat(int32 BoatID, int32 PlayerIndex) {
	// IDからパラメータを取得する
	if (!BoatDataAsset->Data.IsValidIndex(BoatID)) {
		UE_LOG(LogBoat, Error, TEXT("Boat parameter is not defined."));
		return;
	}

	//パラメータを必要な変数に代入していく
	const FBoatParameterRecord Parameter = BoatDataAsset->Data[BoatID];
	BoatMover->SetParameter(Parameter.MaxSpeed, Parameter.Acceleration, Parameter.Control);
	this->StaticMesh->SetStaticMesh(Parameter.BoatMesh);
	this->StaticMesh->SetMaterial(0, Parameter.Materials[PlayerIndex]);
	this->StaticMesh->SetMassOverrideInKg(NAME_None, Parameter.Mass);
}

//レースの準備
void ABoat::RaceReady(ACheckPoint* StartCheckPoint) {
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, TEXT("RaceReady Called!"));
	//最初のチェックポイントを設定する
	NextCheckPoint = StartCheckPoint;
	//直線移動するよう設定
	MoveType = EBoatMovableType::StraightOnly;
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

//移動力を計算する
void ABoat::CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const {
	const FInputInfo InputInfo = IDriver::Execute_CurrentInputInfo(Driver.GetObject());
	const float MinValue = FMath::Min(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);

	switch (MoveType) {
		case EBoatMovableType::Default:
			MoveValue = MinValue;
			LeftValue = InputInfo.LeftMotorValue - MinValue;
			RightValue = InputInfo.RightMotorValue - MinValue;
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
			LeftValue = 0.0f;
			RightValue = 0.0f;
			break;
			//その他
		default:
			UE_LOG(LogTemp, Error, TEXT("Unconfirmed enum EBoatMovableType encounter."));
			break;
	}
}

//反対方向に移動中か
bool ABoat::IsReverseDriving() const {
	if (NextCheckPoint == nullptr) {
		return false;
	}
	//正面とのベクトルで判定する
	const FVector ForwardVector = GetActorForwardVector();
	const FVector To = NextCheckPoint->GetActorLocation() - GetActorLocation();
	const float Dot = ForwardVector.CosineAngle2D(To);
	return Dot < 0.0f;
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

	//音源に対するパラメータ設定
	MoveSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
	ScrewSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
