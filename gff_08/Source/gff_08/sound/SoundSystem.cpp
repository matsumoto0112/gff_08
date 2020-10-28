// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundSystem.h"

#include "gff_08/utils/MyLogCategory.h"

#include <Kismet/GameplayStatics.h>

// 初期化
void USoundSystem::Init(USoundDataAsset* Asset) {
	this->SoundDataAsset = Asset;
}

// 音源の再生
ASoundObject* USoundSystem::PlaySound(ESoundResourceType Sound, bool bAutoDelete) {
	FSoundDataAssetRecord* Asset = SoundDataAsset->Data.Find(Sound);
	if (!Asset) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("不明な音源が再生されようとしました。"));
		}
		UE_LOG(LogSound, Error, TEXT("不明な音源が再生されようとしました。"));
		return nullptr;
	}

	ASoundObject* SoundObject = GetWorld()->SpawnActor<ASoundObject>();
	SoundObject->Init(Asset->Sound, bAutoDelete);
	return SoundObject;
}
