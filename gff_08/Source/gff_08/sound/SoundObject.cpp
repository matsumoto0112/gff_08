// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundObject.h"

ASoundObject::ASoundObject() {
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->OnAudioFinished.AddDynamic(this, &ASoundObject::AudioPlayFinished);
}

void ASoundObject::BeginPlay() {
	Super::BeginPlay();
}

void ASoundObject::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
}

void ASoundObject::Init(USoundBase* Sound, bool bAutoDeleteFlag) {
	AudioComponent->SetSound(Sound);
	AudioComponent->Play();

	this->bAutoDelete = bAutoDeleteFlag;
}

void ASoundObject::Stop() {
	AudioComponent->Stop();
}

void ASoundObject::AudioPlayFinished() {
	if (bAutoDelete) {
		Destroy();
	}
}
