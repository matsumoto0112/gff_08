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
	 * �ʏ�̉����Đ�
	 * @param Sound �����̎��
	 */
	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	ASoundObject* PlaySound(ESoundResourceType Sound);

protected:
	UPROPERTY()
	USoundDataAsset* SoundDataAsset;
};
