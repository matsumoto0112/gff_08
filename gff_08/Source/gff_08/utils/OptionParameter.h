// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/NoExportTypes.h"

#include "OptionParameter.generated.h"

/**
 * ユーザー変更可能なパラメータ管理
 */
UCLASS()
class GFF_08_API UOptionParameter : public USaveGame {
	GENERATED_BODY()

public:
	UOptionParameter();
	~UOptionParameter();

	/**
	 * デフォルトの値をセットする
	 */
	UFUNCTION(BlueprintCallable, Category = "OptionParameter")
	void SetDefaults();

	/**
	 * マスターボリュームの値を設定する
	 */
	UFUNCTION(BlueprintSetter)
	void SetMasterVolume(float Value) {
		MasterVolume = Value;
	}
	/**
	 * マスターボリュームの値を取得する
	 */
	UFUNCTION(BlueprintGetter)
	float GetMasterVolume() const {
		return MasterVolume;
	}
	/**
	 * BGMボリュームの値を設定する
	 */
	UFUNCTION(BlueprintSetter)
	void SetBGMVolume(float Value) {
		BGMVolume = Value;
	}
	/**
	 * BGMボリュームの値を取得する
	 */
	UFUNCTION(BlueprintGetter)
	float GetBGMVolume() const {
		return BGMVolume;
	}
	/**
	 * SEボリュームの値を設定する
	 */
	UFUNCTION(BlueprintSetter)
	void SetSEVolume(float Value) {
		SEVolume = Value;
	}
	/**
	 * SEボリュームの値を取得する
	 */
	UFUNCTION(BlueprintGetter)
	float GetSEVolume() const {
		return SEVolume;
	}
	/**
	 * 反転入力が有効かどうかの値を設定する
	 */
	UFUNCTION(BlueprintSetter)
	void SetFlipInput(bool Value) {
		bFlipInput = Value;
	}
	/**
	 * 反転入力が有効かどうかの値を取得する
	 */
	UFUNCTION(BlueprintGetter)
	bool GetFlipInput() const {
		return bFlipInput;
	}
	/**
	 * オプションデータを保存する
	 */
	UFUNCTION(BlueprintCallable, Category = "Option")
	void SaveOptionData();
	/**
	 * オプションデータを読み込む
	 */
	UFUNCTION(BlueprintCallable, Category = "Option")
	void LoadOptionData();

private:
	static const FString SaveSlotName;
	static const uint32 UserIndex;

	//! マスターボリューム
	UPROPERTY(VisibleAnywhere, BlueprintSetter = SetMasterVolume, BlueprintGetter = GetMasterVolume, Category = "OptionParameter")
	float MasterVolume;
	//! BGMボリューム
	UPROPERTY(VisibleAnywhere, BlueprintSetter = SetBGMVolume, BlueprintGetter = GetBGMVolume, Category = "OptionParameter")
	float BGMVolume;
	//! SEボリューム
	UPROPERTY(VisibleAnywhere, BlueprintSetter = SetSEVolume, BlueprintGetter = GetSEVolume, Category = "OptionParameter")
	float SEVolume;
	//! 反転入力を有効にするか
	UPROPERTY(VisibleAnywhere, BlueprintSetter = SetFlipInput, BlueprintGetter = GetFlipInput, Category = "OptionParameter")
	bool bFlipInput;
};
