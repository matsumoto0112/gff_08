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

UCLASS(BlueprintType)
class GFF_08_API UAllRacersGamePlayDataObject : public UObject {
	GENERATED_BODY()
public:
	UAllRacersGamePlayDataObject() {
	}

	//! プレイヤー1のプレイデータ
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	FGamePlayData Player1Data;
	//! プレイヤー2のプレイデータ
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	FGamePlayData Player2Data;
	//! プレイヤー3のプレイデータ
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	FGamePlayData Player3Data;
	//! プレイヤー4のプレイデータ
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	FGamePlayData Player4Data;
};

UCLASS()
class GFF_08_API UPlayDataNormalizer : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "PlayDataNormalizer")
	static FGamePlayData NormalizePlayData(const FGamePlayData& Data);
};
