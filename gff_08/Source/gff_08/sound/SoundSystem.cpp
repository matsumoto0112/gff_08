// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundSystem.h"

#include "gff_08/utils/MyLogCategory.h"

#include <Kismet/GameplayStatics.h>

// ������
void USoundSystem::Init(USoundDataAsset* Asset) {
	this->SoundDataAsset = Asset;
}

void USoundSystem::PlayBGM(ESoundResourceType Sound) {
	StopBGM();
	BGMComp = UGameplayStatics::SpawnSound2D(GetWorld(), GetRecord(Sound)->Sound, 1.0f, 1.0f, 0.0f, nullptr, true);
}

void USoundSystem::StopBGM() {
	if (BGMComp) {
		BGMComp->Stop();
	}
}

// �����̍Đ�
void USoundSystem::PlaySound2D(ESoundResourceType Sound) {
	FSoundDataAssetRecord* Asset = GetRecord(Sound);
	if (!Asset) {
		return;
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), Asset->Sound, 1.0f, 1.0f, 0.0f, nullptr, true);
}

ASoundObject* USoundSystem::PlaySoundWithAttachOwnerActor(ESoundResourceType Sound, AActor* OwnerActor, bool bAutoDelete) {
	FSoundDataAssetRecord* Asset = GetRecord(Sound);
	if (!Asset) {
		return nullptr;
	}

	ASoundObject* SoundObject = GetWorld()->SpawnActor<ASoundObject>();
	SoundObject->Init(Asset->Sound, Asset->SoundAttenuation, OwnerActor, bAutoDelete);
	return SoundObject;
}

ASoundObject* USoundSystem::PlaySoundAtLocation(ESoundResourceType Sound, const FVector& Location, bool bAutoDelete) {
	FSoundDataAssetRecord* Asset = GetRecord(Sound);
	if (!Asset) {
		return nullptr;
	}

	ASoundObject* SoundObject = GetWorld()->SpawnActor<ASoundObject>();
	SoundObject->Init(Asset->Sound, Asset->SoundAttenuation, Location, bAutoDelete);
	return SoundObject;
}

void USoundSystem::RegisterBGMPlayPercent(const USoundWave* SoundWave, float Percent) {
	this->LastPlayedLocation = Percent;
}

FSoundDataAssetRecord* USoundSystem::GetRecord(ESoundResourceType Sound) const {
	FSoundDataAssetRecord* Asset = SoundDataAsset->Data.Find(Sound);
	if (!Asset) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("�s���ȉ������Đ�����悤�Ƃ��܂����B"));
		}
		UE_LOG(LogSound, Error, TEXT("�s���ȉ������Đ�����悤�Ƃ��܂����B"));
		return nullptr;
	}
	return Asset;
}
