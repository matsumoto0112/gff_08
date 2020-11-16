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
	UTexture2D* StageImage;
	//! ステージの形状レベル名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	FName StageShapeLevelName;
};

USTRUCT(BlueprintType)
struct GFF_08_API FStageDataAssetRecord {
	GENERATED_USTRUCT_BODY()

	//! 内部ステージ番号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 StageIndex;
	//! ゲームのラップ数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 LapCount = 3;
	//! ステージ名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	FString StageName;
	//! ステージ名画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	UTexture2D* StageNameImage;
	//! ミニマップ画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	UTexture2D* MinimapImage;
	//! ステージ外観画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	UTexture2D* StageImage;
	//! ステージの形状レベル名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	FName StageShapeLevelName;
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

	//! データ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageDataAsset")
	TArray<FStageDataAssetRecord> Data;
};
