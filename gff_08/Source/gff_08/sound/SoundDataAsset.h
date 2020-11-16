// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Sound/SoundBase.h"

#include "SoundDataAsset.generated.h"

/**
 * 音源の種類
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
 * 音データ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FSoundData : public FTableRowBase {
	GENERATED_USTRUCT_BODY()

	/**
	 * デフォルトコンストラクタ
	 */
	FSoundData() : Sound(nullptr), SoundAttenuation(nullptr) {
	}

	/**
	 * コンストラクタ
	 */
	FSoundData(USoundBase* Sound, USoundAttenuation* SoundAttenuation) : Sound(Sound), SoundAttenuation(SoundAttenuation) {
	}

	//! 音源の種類
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundData")
	ESoundResourceType SoudnType;

	//! 音源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundData")
	USoundBase* Sound;

	//! サウンド減衰
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundData")
	USoundAttenuation* SoundAttenuation;
};

/**
 * データアセットに格納する音データ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FSoundDataAssetRecord {
	GENERATED_USTRUCT_BODY()

	//! 音源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundDataAssetRecord")
	USoundBase* Sound;

	//! サウンド減衰
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundDataAssetRecord")
	USoundAttenuation* SoundAttenuation;
};

/**
 * サウンドデータアセット
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
	 * データテーブルからインポートする
	 */
	UFUNCTION(meta = (CallInEditor = "true"))
	void Import();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SoundDataAsset")
	TMap<ESoundResourceType, FSoundDataAssetRecord> Data;
};
