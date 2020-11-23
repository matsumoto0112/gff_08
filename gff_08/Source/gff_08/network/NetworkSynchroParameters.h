// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NetworkSynchroParameters.generated.h"

/**
 * プレイヤーに発生したゲーム内イベント
 */
UENUM(BlueprintType)
enum class EGameEvent : uint8 { START, LAP_1, LAP_2, GOAL, DISCONNECT, NONE };

/**
 * ネットワーク接続時に一度だけ更新されるユーザーデータ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkUserData {
	GENERATED_USTRUCT_BODY()

	//! プレイヤー番号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 PlayerIndex = -1;
	//! プレイヤー名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FName PlayerName;
	//! 選択したボート番号
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 BoatIndex = -1;
};

/**
 * 毎フレーム更新される入力情報
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkInputData {
	GENERATED_USTRUCT_BODY()
	// 入力情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float LeftMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float RightMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	bool bBack;
};

/**
 * たまに更新されるイベント発行等のデータ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkEventData {
	GENERATED_USTRUCT_BODY()
	//! 特定のタイミングで同期するための座標（60フレームかに一回更新する）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FVector FixLocation;

	//! 最後に発生したイベント
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	EGameEvent CurrentEvent;
};

/**
 * リザルト時に必要なデータ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkResultData {
	GENERATED_USTRUCT_BODY()

	//! ゴール時に必要な情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	float ConfirmLapTime_3;
};
