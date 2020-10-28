// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundSystem.h"

#include "gff_08/utils/MyLogCategory.h"

#include <Kismet/GameplayStatics.h>

// ������
void USoundSystem::Init(USoundDataAsset* Asset) {
	this->SoundDataAsset = Asset;
}

// �����̍Đ�
ASoundObject* USoundSystem::PlaySound(ESoundResourceType Sound, bool bAutoDelete) {
	FSoundDataAssetRecord* Asset = SoundDataAsset->Data.Find(Sound);
	if (!Asset) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("�s���ȉ������Đ�����悤�Ƃ��܂����B"));
		}
		UE_LOG(LogSound, Error, TEXT("�s���ȉ������Đ�����悤�Ƃ��܂����B"));
		return nullptr;
	}

	ASoundObject* SoundObject = GetWorld()->SpawnActor<ASoundObject>();
	SoundObject->Init(Asset->Sound, bAutoDelete);
	return SoundObject;
}
