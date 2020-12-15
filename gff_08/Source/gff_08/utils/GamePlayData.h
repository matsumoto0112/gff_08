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

	//! �v���C���[1�̃v���C�f�[�^
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	FGamePlayData Player1Data;
	//! �v���C���[2�̃v���C�f�[�^
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	FGamePlayData Player2Data;
	//! �v���C���[3�̃v���C�f�[�^
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AllRacersGamePlayData")
	FGamePlayData Player3Data;
	//! �v���C���[4�̃v���C�f�[�^
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
