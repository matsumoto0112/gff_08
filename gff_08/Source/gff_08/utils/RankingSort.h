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
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static FAllRacersGamePlayData SortByLapTimes(const FAllRacersGamePlayData& RacersPlayData);

	/**
	 * �����L���O���Ƀ\�[�g���ꂽ�e�v���C���[�̃f�[�^���擾����
	 */
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static TArray<FGamePlayData> GetPlayDatasSortedByRanking(const FAllRacersGamePlayData& Data);

	/**
	* ���v�N���A�^�C�����擾����
	*/
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static float GetSumTimes(const FGamePlayData& Data);
};
