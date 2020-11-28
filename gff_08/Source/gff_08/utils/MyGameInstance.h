// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "gff_08/network/NetworkData.h"
#include "gff_08/sound/SoundDataAsset.h"
#include "gff_08/sound/SoundSystem.h"
#include "gff_08/utils/GamePlayData.h"
#include "gff_08/utils/OptionParameter.h"
#include "gff_08/utils/PlayUserData.h"

#include "MyGameInstance.generated.h"

/**
 * ゲーム中に常に存在するインスタンス
 */
UCLASS()
class GFF_08_API UMyGameInstance : public UGameInstance {
	GENERATED_BODY()

private:
	/**
	 * コンストラクタ
	 */
	UMyGameInstance();

public:
	/**
	 * 初期化
	 */
	virtual void Init() override;

	/**
	 * 終了時処理
	 */
	virtual void Shutdown() override;
	/**
	 * 実行中のBlueprintのコールスタックをログ出力する
	 */
	UFUNCTION(BlueprintCallable, Category = "Debug")
	static void PrintLogBlueprintCallstack();
	/**
	 * インスタンスの取得
	 */
	UFUNCTION(BlueprintPure, Category = "MyGameInstance")
	static UMyGameInstance* GetInstance();
	/**
	 * サウンドシステムの取得
	 */
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	USoundSystem* GetSoundSystem() const;

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	FAllRacersGamePlayData GetPlayData() const {
		return PlayData;
	}

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	void SetPlayData(const FAllRacersGamePlayData& Data) {
		this->PlayData = Data;
		if (this->PlayData.Player1Data.LapTimes.Num() == 3) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
					this->PlayData.Player1Data.LapTimes[0], this->PlayData.Player1Data.LapTimes[1],
					this->PlayData.Player1Data.LapTimes[2]));
			UE_LOG(LogTemp, Log, TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
				this->PlayData.Player1Data.LapTimes[0], this->PlayData.Player1Data.LapTimes[1],
				this->PlayData.Player1Data.LapTimes[2]);
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Player1Data LapTimes.Num() != 3... Num = "), this->PlayData.Player1Data.LapTimes.Num()));
			UE_LOG(LogTemp, Log, TEXT("Player1Data LapTimes.Num() != 3... Num = "), this->PlayData.Player1Data.LapTimes.Num());
		}
		if (this->PlayData.Player2Data.LapTimes.Num() == 3) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
					this->PlayData.Player2Data.LapTimes[0], this->PlayData.Player2Data.LapTimes[1],
					this->PlayData.Player2Data.LapTimes[2]));
			UE_LOG(LogTemp, Log, TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
				this->PlayData.Player2Data.LapTimes[0], this->PlayData.Player2Data.LapTimes[1],
				this->PlayData.Player2Data.LapTimes[2]);

		} else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Player2Data LapTimes.Num() != 3... Num = "), this->PlayData.Player2Data.LapTimes.Num()));
			UE_LOG(LogTemp, Log, TEXT("Player1Data LapTimes.Num() != 3... Num = "), this->PlayData.Player2Data.LapTimes.Num());
		}
		if (this->PlayData.Player3Data.LapTimes.Num() == 3) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
					this->PlayData.Player3Data.LapTimes[0], this->PlayData.Player3Data.LapTimes[1],
					this->PlayData.Player3Data.LapTimes[2]));
			UE_LOG(LogTemp, Log, TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
				this->PlayData.Player3Data.LapTimes[0], this->PlayData.Player3Data.LapTimes[1],
				this->PlayData.Player3Data.LapTimes[2]);

		} else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Player3Data LapTimes.Num() != 3... Num = "), this->PlayData.Player3Data.LapTimes.Num()));
			UE_LOG(LogTemp, Log, TEXT("Player1Data LapTimes.Num() != 3... Num = "), this->PlayData.Player3Data.LapTimes.Num());
		}
		if (this->PlayData.Player4Data.LapTimes.Num() == 3) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
					this->PlayData.Player4Data.LapTimes[0], this->PlayData.Player4Data.LapTimes[1],
					this->PlayData.Player4Data.LapTimes[2]));
			UE_LOG(LogTemp, Log, TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
				this->PlayData.Player4Data.LapTimes[0], this->PlayData.Player4Data.LapTimes[1],
				this->PlayData.Player4Data.LapTimes[2]);
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Player4Data LapTimes.Num() != 3... Num = "), this->PlayData.Player4Data.LapTimes.Num()));
			UE_LOG(LogTemp, Log, TEXT("Player4Data LapTimes.Num() != 3... Num = "), this->PlayData.Player4Data.LapTimes.Num());
		}
	}

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UOptionParameter* GetOption() const {
		return Option;
	}
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UPlayUserData* GetUserData() const {
		return UserData;
	}
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UNetworkData* GetNetworkData() const {
		return NetworkData;
	}

protected:
	//! OnHandleSystemError デリゲート登録時のハンドル
	FDelegateHandle OnSystemErrorDelegateHandle;
	/**
	 * システムエラー時に呼ばれる関数
	 */
	void OnSystemError();

protected:
	//! サウンドデータのアセット
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundDataAsset* SoundDataAsset;

protected:
	//! サウンドシステム
	UPROPERTY()
	USoundSystem* SoundSystem;
	//! ゲームのプレイ情報
	UPROPERTY()
	FAllRacersGamePlayData PlayData;
	//! オプション情報
	UPROPERTY()
	UOptionParameter* Option;
	//! ユーザーの情報
	UPROPERTY()
	UPlayUserData* UserData;
	//! ネットワークの情報
	UPROPERTY()
	UNetworkData* NetworkData;
};
