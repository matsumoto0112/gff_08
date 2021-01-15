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
	 * ランキング順にソートされた各プレイヤーのデータを取得する
	 */
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static TArray<FGamePlayData> GetPlayDatasSortedByRanking();

	/**
	 * 合計クリアタイムを取得する
	 */
	UFUNCTION(BlueprintCallable, Category = "RankingSort")
	static float GetSumTimes(const FGamePlayData& Data);
	/**
	 * 自分のリザルト情報を取得する
	 */
	UFUNCTION(BlueprintPure, Category = "RankingSort")
	static FGamePlayData GetMyPlayerResultData();

	UFUNCTION(BlueprintPure, Category = "RankingSort")
	static int32 UngoalPlayerRankingNumber();
};
