// Fill out your copyright notice in the Description page of Project Settings.

#include "OptionParameter.h"

#include "Engine.h"

const FString UOptionParameter::SaveSlotName = TEXT("Option");
const uint32 UOptionParameter::UserIndex = 0;

UOptionParameter::UOptionParameter() {
}

UOptionParameter::~UOptionParameter() {
}

void UOptionParameter::SetDefaults() {
	SetMasterVolume(100.0f);
	SetBGMVolume(100.0f);
	SetSEVolume(100.0f);
	SetFlipInput(false);
}

void UOptionParameter::SaveOptionData() {
	UGameplayStatics::SaveGameToSlot(this, SaveSlotName, UserIndex);
}

void UOptionParameter::LoadOptionData() {
	UOptionParameter* Load = Cast<UOptionParameter>(UGameplayStatics::LoadGameFromSlot(this->SaveSlotName, this->UserIndex));

	if (Load) {
		this->MasterVolume = Load->MasterVolume;
		this->BGMVolume = Load->BGMVolume;
		this->SEVolume = Load->SEVolume;
		this->bFlipInput = Load->bFlipInput;
	} else {
		this->SetDefaults();
	}
}
