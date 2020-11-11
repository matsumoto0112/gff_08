// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"

#include "StageDataAsset.generated.h"

/**
 * ステージ情報管理構造体
 */
USTRUCT(BlueprintType)
struct GFF_08_API FStageData : public FTableRowBase {
	GENERATED_USTRUCT_BODY()

	/**
	 * デフォルトコンストラクタ
	 */
	FStageData() : LapCount(0), StageName(TEXT("Default")), StageImages() {
	}

	/**
	 * コンストラクタ
	 */
	FStageData(int32 LapCount, const FString& Name, const TArray<UTexture2D*>& Images)
		: LapCount(LapCount), StageName(Name), StageImages(Images) {
	}

	//! ゲームのラップ数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	int32 LapCount = 3;
	//! ステージ名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	FString StageName;
	//! ステージ名画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	UTexture2D* StageNameImage;
	//! ミニマップ画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	UTexture2D* MinimapImage;
	//! ステージ外観画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	TArray<UTexture2D*> StageImages;
};

USTRUCT(BlueprintType)
struct GFF_08_API FStageDataAssetRecord {
	GENERATED_USTRUCT_BODY()

	//! 内部ステージ番号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 StageIndex;
	//! ゲームのラップ数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 LapCount;
	//! ステージ名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	FString StageName;
	//! ステージ名画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	UTexture2D* StageNameImage;
	//! ミニマップ画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	UTexture2D* MinimapImage;
	//! ステージ外観画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	TArray<UTexture2D*> StageImages;
};

/**
 *
 */
UCLASS(BlueprintType)
class GFF_08_API UStageDataAsset : public UDataAsset {
	GENERATED_BODY()
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "StageDataAsset")
	UDataTable* DataTable;
#endif
	/**
	 * データテーブルからインポートする
	 */
	UFUNCTION(meta = (CallInEditor = "true"))
	void Import();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageDataAsset")
	TArray<FStageDataAssetRecord> Data;
};
