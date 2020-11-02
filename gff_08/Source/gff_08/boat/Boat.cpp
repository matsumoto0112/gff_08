// Fill out your copyright notice in the Description page of Project Settings.

#include "Boat.h"

#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/SpeedConverter.h"

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

float ABoat::GetPlayerSpeed() const {
	return USpeedConverter::ToSpeedKilometerPerHour(GetVelocity().Size());
}

void ABoat::CalcMovementValues(float& MoveValue, float& LeftValue, float& RightValue) const {
	const float MinValue = FMath::Min(LeftMotorValue, RightMotorValue);

	MoveValue = MinValue;
	LeftValue = LeftMotorValue - MinValue;
	RightValue = RightMotorValue - MinValue;
}

// Called every frame
void ABoat::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	MoveSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
	ScrewSound->GetAudioComponent()->SetFloatParameter(TEXT("Speed"), GetPlayerSpeed());
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
