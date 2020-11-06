// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

#include "Engine/Engine.h"

UMyGameInstance::UMyGameInstance() {
	SoundSystem = CreateDefaultSubobject<USoundSystem>(TEXT("SoundSystem"));
}

void UMyGameInstance::Init() {
	Super::Init();
	OnSystemErrorDelegateHandle = FCoreDelegates::OnHandleSystemError.AddUObject(this, &UMyGameInstance::OnSystemError);

	SoundSystem->Init(SoundDataAsset);
}

void UMyGameInstance::Shutdown() {
	FCoreDelegates::OnHandleSystemError.Remove(OnSystemErrorDelegateHandle);
	Super::Shutdown();
}

void UMyGameInstance::PrintLogBlueprintCallstack() {
	FString Callstack = FFrame::GetScriptCallstack();

	UE_LOG(LogTemp, Error, TEXT("--------------------------------------"));
	UE_LOG(LogTemp, Error, TEXT(" Blueprint Callstack:\n%s"), *Callstack);
	UE_LOG(LogTemp, Error, TEXT("--------------------------------------"));
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

void UMyGameInstance::OnSystemError() {
	PrintLogBlueprintCallstack();
}
