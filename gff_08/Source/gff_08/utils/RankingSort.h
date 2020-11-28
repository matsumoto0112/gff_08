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
	 * ランキング順にソートされた各プレイヤーのデータを取得する
	 */
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static TArray<FGamePlayData> GetPlayDatasSortedByRanking(const FAllRacersGamePlayData& Data);

	/**
	* 合計クリアタイムを取得する
	*/
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static float GetSumTimes(const FGamePlayData& Data);
};
