// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "gff_08/sound/SoundDataAsset.h"
#include "gff_08/sound/SoundObject.h"

#include "SoundSystem.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API USoundSystem : public UObject {
	GENERATED_BODY()

public:
	/**
	 * ������
	 * @param Asset �T�E���h�A�Z�b�g
	 */
	void Init(USoundDataAsset* Asset);
	/**
	 * BGM�̍Đ�
	 * @param Sound �����̎��
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	void PlayBGM(ESoundResourceType Sound);
	/**
	 * BGM�̒�~
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	void StopBGM();
	/**
	 * �ʏ�̉����Đ�
	 * @param Sound �����̎��
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	ASoundObject* PlaySound2D(ESoundResourceType Sound, bool bAutoDelete = true);
	/**
	 * �A�N�^�[�ɒǏ]���A�����Đ�����
	 * @param Sound �����̎��
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	ASoundObject* PlaySoundWithAttachOwnerActor(ESoundResourceType Sound, AActor* OwnerActor, bool bAutoDelete = true);
	/**
	 * ������W�ŉ����Đ�����
	 * @param Sound �����̎��
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	ASoundObject* PlaySoundAtLocation(ESoundResourceType Sound, const FVector& Location, bool bAutoDelete = true);
	UFUNCTION(Category = "SoundSystem")
	void RegisterBGMPlayPercent(const USoundWave* SoundWave, float Percent);

private:
	FSoundDataAssetRecord* GetRecord(ESoundResourceType Sound) const;

protected:
	UPROPERTY()
	USoundDataAsset* SoundDataAsset;

	UPROPERTY()
	UAudioComponent* BGMComp;
	ESoundResourceType BGMType;
	float LastPlayedLocation;
};
