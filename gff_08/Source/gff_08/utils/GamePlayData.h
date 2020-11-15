// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GamePlayData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct GFF_08_API FGamePlayData {
	GENERATED_USTRUCT_BODY()
	FGamePlayData() : Ranking(1), LapTimes() {
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GamePlayData")
	int32 Ranking;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GamePlayData")
	TArray<float> LapTimes;
};
