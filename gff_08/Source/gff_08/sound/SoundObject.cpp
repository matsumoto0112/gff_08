// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundObject.h"

ASoundObject::ASoundObject() {
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->OnAudioFinished.AddDynamic(this, &ASoundObject::AudioPlayFinished);
	RootComponent = AudioComponent;

	PrimaryActorTick.bCanEverTick = false;
}

void ASoundObject::BeginPlay() {
	Super::BeginPlay();
}

void ASoundObject::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
}

void ASoundObject::Init(USoundBase* Sound, bool bAutoDeleteFlag) {
	this->bAutoDelete = bAutoDeleteFlag;
	bAudioPlayFinished = false;
	AudioComponent->SetSound(Sound);
	AudioComponent->Play();
}

void ASoundObject::Init(USoundBase* Sound, USoundAttenuation* SoundAttenuation, AActor* OwnerActor, bool bAutoDeleteFlag) {
	this->AttachToActor(OwnerActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	this->bAutoDelete = bAutoDeleteFlag;
	bAudioPlayFinished = false;
	AudioComponent->SetSound(Sound);
	AudioComponent->AttenuationSettings = SoundAttenuation;
	AudioComponent->Play();
}

void ASoundObject::Init(USoundBase* Sound, USoundAttenuation* SoundAttenuation, const FVector& Location, bool bAutoDeleteFlag) {
	this->SetActorLocation(Location);
	this->bAutoDelete = bAutoDeleteFlag;
	bAudioPlayFinished = false;

	AudioComponent->SetSound(Sound);
	AudioComponent->AttenuationSettings = SoundAttenuation;
	AudioComponent->Play();
}

void ASoundObject::Stop() {
	AudioComponent->Stop();
}

void ASoundObject::AudioPlayFinished() {
	if (bAutoDelete) {
		Destroy();
	}
	bAudioPlayFinished = true;
}

bool ASoundObject::IsFinished() const {
	return bAudioPlayFinished;
}
