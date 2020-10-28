// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

#include "Engine/Engine.h"

UMyGameInstance::UMyGameInstance() {
	SoundSystem = CreateDefaultSubobject<USoundSystem>(TEXT("SoundSystem"));
}

void UMyGameInstance::Init() {
	SoundSystem->Init(SoundDataAsset);
}

void UMyGameInstance::Shutdown()
{
}

UMyGameInstance* UMyGameInstance::GetInstance() {
	UMyGameInstance* Instance = nullptr;

	if (GEngine) {
		FWorldContext* Context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		Instance = Cast<UMyGameInstance>(Context->OwningGameInstance);
	}

	return Instance;
}

USoundSystem* UMyGameInstance::GetSoundSystem() const {
	return SoundSystem;
}
