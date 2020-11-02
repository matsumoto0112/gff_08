// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundSystem.h"

#include "gff_08/utils/MyLogCategory.h"

#include <Kismet/GameplayStatics.h>

// 初期化
void USoundSystem::Init(USoundDataAsset* Asset) {
	this->SoundDataAsset = Asset;
}

// 音源の再生
ASoundObject* USoundSystem::PlaySound2D(ESoundResourceType Sound, bool bAutoDelete) const {
	FSoundDataAssetRecord* Asset = GetRecord(Sound);
	if (!Asset) {
		return nullptr;
	}

	ASoundObject* SoundObject = GetWorld()->SpawnActor<ASoundObject>();
	SoundObject->Init(Asset->Sound, bAutoDelete);
	return SoundObject;
}

ASoundObject* USoundSystem::PlaySoundWithAttachOwnerActor(ESoundResourceType Sound, AActor* OwnerActor, bool bAutoDelete) const {
	FSoundDataAssetRecord* Asset = GetRecord(Sound);
	if (!Asset) {
		return nullptr;
	}

	ASoundObject* SoundObject = GetWorld()->SpawnActor<ASoundObject>();
	SoundObject->Init(Asset->Sound, Asset->SoundAttenuation, OwnerActor, bAutoDelete);
	return SoundObject;
}

ASoundObject* USoundSystem::PlaySoundAtLocation(ESoundResourceType Sound, const FVector& Location, bool bAutoDelete) const {
	FSoundDataAssetRecord* Asset = GetRecord(Sound);
	if (!Asset) {
		return nullptr;
	}

	ASoundObject* SoundObject = GetWorld()->SpawnActor<ASoundObject>();
	SoundObject->Init(Asset->Sound, Asset->SoundAttenuation, Location, bAutoDelete);
	return SoundObject;
}

FSoundDataAssetRecord* USoundSystem::GetRecord(ESoundResourceType Sound) const {
	FSoundDataAssetRecord* Asset = SoundDataAsset->Data.Find(Sound);
	if (!Asset) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("不明な音源が再生されようとしました。"));
		}
		UE_LOG(LogSound, Error, TEXT("不明な音源が再生されようとしました。"));
		return nullptr;
	}
	return Asset;
}
