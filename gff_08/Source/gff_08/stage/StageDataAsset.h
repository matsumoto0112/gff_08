// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"

#include "StageDataAsset.generated.h"

/**
 * �X�e�[�W���Ǘ��\����
 */
USTRUCT(BlueprintType)
struct GFF_08_API FStageData : public FTableRowBase {
	GENERATED_USTRUCT_BODY()

	/**
	 * �f�t�H���g�R���X�g���N�^
	 */
	FStageData() : LapCount(0), StageName(TEXT("Default")) {
	}

	/**
	 * �R���X�g���N�^
	 */
	FStageData(int32 LapCount, const FString& Name) : LapCount(LapCount), StageName(Name) {
	}

	//! �Q�[���̃��b�v��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	int32 LapCount;

	//! �X�e�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	FString StageName;
};

USTRUCT(BlueprintType)
struct GFF_08_API FStageDataAssetRecord {
	GENERATED_USTRUCT_BODY()

	//! �Q�[���̃��b�v��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 LapCount;

	//! �X�e�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	FString StageName;

	//! �����X�e�[�W�ԍ�
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