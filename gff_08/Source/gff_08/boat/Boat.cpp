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

	MoveType = EBoatMovableType::NoMove;

	const UMyGameInstance* Instance = UMyGameInstance::GetInstance();
	const USoundSystem* SoundSystem = Instance->GetSoundSystem();
	MoveSound = SoundSystem->PlaySoundWithAttachOwnerActor(ESoundResourceType::SE_BOAT_MOVE, this, false);
	ScrewSound = SoundSystem->PlaySoundWithAttachOwnerActor(ESoundResourceType::SE_BOAT_SCREW, this, false);
}

void ABoat::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	MoveSound->Stop();
	ScrewSound->Stop();
}

void ABoat::ChangeBoat(int32 BoatID) {
	if (!BoatDataAsset->Data.IsValidIndex(BoatID)) {
		UE_LOG(LogBoat, Error, TEXT("Boat parameter is not defined."));
		return;
	}

	const FBoatParameterRecord Parameter = BoatDataAsset->Data[BoatID];
	BoatMover->SetParameter(Parameter.MaxSpeed, Parameter.Acceleration, Parameter.Control);
}

void ABoat::RaceReady(ACheckPoint* StartCheckPoint) {
	NextCheckPoint = StartCheckPoint;
	MoveType = EBoatMovableType::StraightOnly;
}

void ABoat::RaceStart() {
	MoveType = EBoatMovableType::Default;
}

float ABoat::GetPlayerSpeed() const {
	return USpeedConverter::ToSpeedKilometerPerHour(GetVelocity().Size());
}

void ABoat::CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const {
	const FInputInfo InputInfo = IDriver::Execute_CurrentInputInfo(Driver.GetObject());
	const float MinValue = FMath::Min(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);

	switch (MoveType) {
		case EBoatMovableType::Default:
			MoveValue = MinValue;
			LeftValue = InputInfo.LeftMotorValue - MinValue;
			RightValue = InputInfo.RightMotorValue - MinValue;
			break;
		case EBoatMovableType::NoMove:
			MoveValue = 0.0f;
			LeftValue = 0.0f;
			RightValue = 0.0f;
			break;
		case EBoatMovableType::StraightOnly:
			MoveValue = 0.8f;
			LeftValue = 0.0f;
			RightValue = 0.0f;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Unconfirmed enum EBoatMovableType encounter."));
			break;
	}
}

bool ABoat::IsReverseDriving() const {
	const FVector ForwardVector = GetActorForwardVector();
	const FVector To = NextCheckPoint->GetActorLocation() - GetActorLocation();
	const float Dot = ForwardVector.CosineAngle2D(To);
	return Dot < 0.0f;
}

// Called every frame
void ABoat::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	IDriver::Execute_UpdateInputInfo(Driver.GetObject());

	float MoveValue;
	float LeftValue;
	float RightValue;
	CalcMovementValues(MoveValue, LeftValue, RightValue);
	BoatMover->Move(MoveValue, LeftValue, RightValue);

	MoveSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
	ScrewSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
