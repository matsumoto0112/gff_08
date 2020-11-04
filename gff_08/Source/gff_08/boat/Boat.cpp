// Fill out your copyright notice in the Description page of Project Settings.

#include "Boat.h"

#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/SpeedConverter.h"
#include "kismet/KismetSystemLibrary.h"

// Sets default values
ABoat::ABoat() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoat::BeginPlay() {
	Super::BeginPlay();

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

void ABoat::RaceReady(ACheckPoint* StartCheckPoint, const FVector& StartLocation) {
	NextCheckPoint = StartCheckPoint;
	SetActorLocation(StartLocation);
}

float ABoat::GetPlayerSpeed() const {
	return USpeedConverter::ToSpeedKilometerPerHour(GetVelocity().Size());
}

void ABoat::CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const {
	const FInputInfo InputInfo = IDriver::Execute_CurrentInputInfo(Driver.GetObject());
	const float MinValue = FMath::Min(InputInfo.LeftMotorValue, InputInfo.RightMotorValue);

	MoveValue = MinValue;
	LeftValue = InputInfo.LeftMotorValue - MinValue;
	RightValue = InputInfo.RightMotorValue - MinValue;
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

	MoveSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
	ScrewSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());

	const FVector UpVector = GetActorUpVector();
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
