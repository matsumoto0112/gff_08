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
	FStageData() : LapCount(0), StageName(TEXT("Default")), StageImages() {
	}

	/**
	 * �R���X�g���N�^
	 */
	FStageData(int32 LapCount, const FString& Name, const TArray<UTexture2D*>& Images)
		: LapCount(LapCount), StageName(Name), StageImages(Images) {
	}

	//! �Q�[���̃��b�v��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	int32 LapCount = 3;
	//! �X�e�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	FString StageName;
	//! �X�e�[�W���摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	UTexture2D* StageNameImage;
	//! �~�j�}�b�v�摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	UTexture2D* MinimapImage;
	//! �X�e�[�W�O�ω摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	TArray<UTexture2D*> StageImages;
};

USTRUCT(BlueprintType)
struct GFF_08_API FStageDataAssetRecord {
	GENERATED_USTRUCT_BODY()

	//! �����X�e�[�W�ԍ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 StageIndex;
	//! �Q�[���̃��b�v��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	int32 LapCount;
	//! �X�e�[�W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	FString StageName;
	//! �X�e�[�W���摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageData")
	UTexture2D* StageNameImage;
	//! �~�j�}�b�v�摜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDataAssetRecord")
	UTexture2D* MinimapImage;
	//! �X�e�[�W�O�ω摜
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
	 * �f�[�^�e�[�u������C���|�[�g����
	 */
	UFUNCTION(meta = (CallInEditor = "true"))
	void Import();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StageDataAsset")
	TArray<FStageDataAssetRecord> Data;
};
