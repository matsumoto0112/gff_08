// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "gff_08/sound/SoundDataAsset.h"
#include "gff_08/sound/SoundSystem.h"
#include "gff_08/utils/GamePlayData.h"
#include "gff_08/utils/OptionParameter.h"

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
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	static UMyGameInstance* GetInstance();
	/**
	 * サウンドシステムの取得
	 */
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	USoundSystem* GetSoundSystem() const;

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	FGamePlayData GetPlayData() const {
		return PlayData;
	}

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	void SetPlayData(const FGamePlayData& Data) {
		this->PlayData = Data;
	}

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UOptionParameter* GetOption() const {
		return Option;
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
	FGamePlayData PlayData;
	//! オプション情報
	UPROPERTY()
	UOptionParameter* Option;
};
