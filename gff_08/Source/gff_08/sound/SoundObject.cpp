// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundObject.h"

ASoundObject::ASoundObject() {
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void ASoundObject::BeginPlay() {
	Super::BeginPlay();
}

void ASoundObject::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
}

void ASoundObject::Init(USoundBase* Sound) {
	AudioComponent->SetSound(Sound);
	AudioComponent->Play();
}

void ASoundObject::Stop() {
	AudioComponent->Stop();
}