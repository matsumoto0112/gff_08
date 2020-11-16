// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Sound/SoundBase.h"

#include "SoundDataAsset.generated.h"

/**
 * �����̎��
 */
UENUM(BlueprintType)
enum class ESoundResourceType : uint8 {
	BGM_TITLE,
	BGM_RACE,
	BGM_GOAL,
	BGM_RESULT,
	SE_BOAT_HIT,
	SE_BOAT_MOVE,
	SE_BOAT_SCREW,
	SE_BOAT_WAVE_BOOST,
	SE_RACE_COUNTDOWN,
	SE_RACE_GOAL,
	SE_RACE_LAP_COUNT,
	SE_RACE_START,
	SE_GENERAL_BACK,
	SE_GENERAL_DECISION,
	SE_GENERAL_SELECT,

	NONE
};

/**
 * ���f�[�^
 */
USTRUCT(BlueprintType)
struct GFF_08_API FSoundData : public FTableRowBase {
	GENERATED_USTRUCT_BODY()

	/**
	 * �f�t�H���g�R���X�g���N�^
	 */
	FSoundData() : Sound(nullptr), SoundAttenuation(nullptr) {
	}

	/**
	 * �R���X�g���N�^
	 */
	FSoundData(USoundBase* Sound, USoundAttenuation* SoundAttenuation) : Sound(Sound), SoundAttenuation(SoundAttenuation) {
	}

	//! �����̎��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundData")
	ESoundResourceType SoudnType;

	//! ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundData")
	USoundBase* Sound;

	//! �T�E���h����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundData")
	USoundAttenuation* SoundAttenuation;
};

/**
 * �f�[�^�A�Z�b�g�Ɋi�[���鉹�f�[�^
 */
USTRUCT(BlueprintType)
struct GFF_08_API FSoundDataAssetRecord {
	GENERATED_USTRUCT_BODY()

	//! ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundDataAssetRecord")
	USoundBase* Sound;

	//! �T�E���h����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundDataAssetRecord")
	USoundAttenuation* SoundAttenuation;
};

/**
 * �T�E���h�f�[�^�A�Z�b�g
 */
UCLASS()
class GFF_08_API USoundDataAsset : public UDataAsset {
	GENERATED_BODY()
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "DataTable")
	UDataTable* DataTable;
#endif

	/**
	 * �f�[�^�e�[�u������C���|�[�g����
	 */
	UFUNCTION(meta = (CallInEditor = "true"))
	void Import();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SoundDataAsset")
	TMap<ESoundResourceType, FSoundDataAssetRecord> Data;
};
