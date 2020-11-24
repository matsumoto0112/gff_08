// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GamePlayData.generated.h"
/**
 *
 */
USTRUCT(BlueprintType)
struct GFF_08_API FGamePlayData {
	GENERATED_USTRUCT_BODY()
	FGamePlayData() : PlayerIndex(-1), RacerName(TEXT("")), LapTimes() {
	}
	FGamePlayData(int32 PlayerIndex, const FName RacerName, const TArray<float> LapTimes)
		: PlayerIndex(PlayerIndex), RacerName(RacerName), LapTimes(LapTimes) {
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GamePlayData")
	int32 PlayerIndex;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GamePlayData")
	FName RacerName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GamePlayData")
	TArray<float> LapTimes;
};

USTRUCT(BlueprintType)
struct GFF_08_API FAllRacersGamePlayData {
	GENERATED_USTRUCT_BODY()
	FAllRacersGamePlayData() : MyBoatIndex(0), AllRacersData() {
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	int32 MyBoatIndex;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	TArray<FGamePlayData> AllRacersData;
};
