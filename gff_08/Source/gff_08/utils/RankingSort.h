// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "gff_08/utils/GamePlayData.h"

#include "RankingSort.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API URankingSort : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	/**
	 * �����L���O���Ƀ\�[�g���ꂽ�e�v���C���[�̃f�[�^���擾����
	 */
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static TArray<FGamePlayData> GetPlayDatasSortedByRanking();

	/**
	 * ���v�N���A�^�C�����擾����
	 */
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static float GetSumTimes(const FGamePlayData& Data);
	/**
	 * �����̃��U���g�����擾����
	 */
	UFUNCTION(BlueprintPure, Category = "RankingSort")
	static FGamePlayData GetMyPlayerResultData();

	UFUNCTION(BlueprintPure, Category = "RankingSort")
	static int32 UngoalPlayerRankingNumber();
};
