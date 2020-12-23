// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NetworkSynchroParameters.generated.h"

/**
 * プレイヤーに発生したゲーム内イベント
 */
UENUM(BlueprintType)
enum class EGameEvent : uint8 {
	SETUP,		   //! セットアップ処理中
	RACEREADY,	   //! 準備完了
	START,		   //! 一週目
	LAP_1,		   //! 二週目
	LAP_2,		   //! 三週目
	GOAL,		   //! ゴールした
	DISCONNECT,	   //! 切断した
	NONE
};

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
	//ネットワーク上のID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 PlayerNetworkID = -1;
};

/**
 * 毎フレーム更新される入力情報
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkInputData {
	GENERATED_USTRUCT_BODY()
	// 入力情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	uint8 CompressionLeftMotorData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	uint8 CompressionRightMotorData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	uint8 CompressionbBackData;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	// float LeftMotorValue;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	// float RightMotorValue;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	// bool bBack;
};

/**
 * 座標系データ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkTransformData {
	GENERATED_USTRUCT_BODY()
	//! 特定のタイミングで同期するための座標（60フレームかに一回更新する）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FVector FixLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FRotator FixRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FVector FixVelocity;

	//! 現在のチェックポイントのインデックス（ランキング計算用）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 CheckPointIndex;
	//! 現在の周回数（ランキング計算用）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	int32 LapCount;
};

/**
 * たまに更新されるイベント発行等のデータ
 */
USTRUCT(BlueprintType)
struct GFF_08_API FNetworkEventData {
	GENERATED_USTRUCT_BODY()
	//! 最後に発生したイベント
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	EGameEvent CurrentEvent;

	//! レースを開始する時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NetworkSynchroParameters")
	FDateTime RaceStartTime;
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
