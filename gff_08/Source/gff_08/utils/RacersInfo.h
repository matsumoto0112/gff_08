// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RacersInfo.generated.h"

/**
 * レーサーの種類
 * PlayerかAIか、AIの種類も含む
 */
UENUM(BlueprintType)
enum class ERacerType : uint8 {
	Player,	   //! プレイヤー操作
	AI,		   //! AI操作
};

/**
 * レーサー個人の情報
 */
USTRUCT(BlueprintType)
struct GFF_08_API FRacerInfo {
	GENERATED_USTRUCT_BODY()

	//! レーサーのID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	int32 RacerID;
	//! レーサーの種類
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	ERacerType RacerType;
};

/**
 * レーサー全体の個人情報
 */
USTRUCT(BlueprintType)
struct GFF_08_API FAllRacerInfo {
	GENERATED_USTRUCT_BODY()

	//! レーサーたちの情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	TArray<FRacerInfo> Racers;
};
