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
	ReplecatedPlayer, //! 複製された方のプレイヤー（マルチプレイ時の対戦相手）
};

/**
 * レーサー個人の情報
 */
USTRUCT(BlueprintType)
struct GFF_08_API FRacerInfo {
	GENERATED_USTRUCT_BODY()
	//! レーサーの名前
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	FName RacerName;
	//! プレイヤー番号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	int32 PlayerIndex;
	//! ボートのインデックス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RacerInfo")
	int32 BoatIndex;
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
