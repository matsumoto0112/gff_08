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
	 * 初期化
	 * @param Asset サウンドアセット
	 */
	void Init(USoundDataAsset* Asset);
	/**
	 * BGMの再生
	 * @param Sound 音源の種類
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	void PlayBGM(ESoundResourceType Sound);
	/**
	 * BGMの停止
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	void StopBGM();
	/**
	 * 通常の音源再生
	 * @param Sound 音源の種類
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	ASoundObject* PlaySound2D(ESoundResourceType Sound, bool bAutoDelete = true);
	/**
	 * アクターに追従し、音を再生する
	 * @param Sound 音源の種類
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	ASoundObject* PlaySoundWithAttachOwnerActor(ESoundResourceType Sound, AActor* OwnerActor, bool bAutoDelete = true);
	/**
	 * 特定座標で音を再生する
	 * @param Sound 音源の種類
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
