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
	FStageData() : LapCount(0), StageName(TEXT("Default")) {
	}

	/**
	 * コンストラクタ
	 */
	FStageData(int32 LapCount, const FString& Name) : LapCount(LapCount), StageName(Name) {
	}

	//! ゲームのラップ数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	int32 LapCount;

	//! ステージ名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	FString StageName;
};

USTRUCT(BlueprintType)
struct GFF_08_API FStageDataAssetRecord {
	GENERATED_USTRUCT_BODY()

	//! ゲームのラップ数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 LapCount;

	//! ステージ名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	FString StageName;

	//! 内部ステージ番号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 StageIndex;
};

/**
 *
 */
UCLASS() class GFF_08_API UStageDataAsset : public UDataAsset {
	GENERATED_BODY()
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "StageDataAsset")
	UDataTable* DataTable;
#endif
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageDataAsset")
	TArray<FStageDataAssetRecord> Data;
};
