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

	FGamePlayData() : Ranking(-1), PlayTime(0.0) {
	}

	FGamePlayData(int32 Ranking, float PlayTime) : Ranking(Ranking), PlayTime(PlayTime) {
	}

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GamePlayData")
	int32 Ranking;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GamePlayData")
	float PlayTime;
};
