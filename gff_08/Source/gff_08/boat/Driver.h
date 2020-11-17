// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Driver.generated.h"

/**
 * ボートに対する入力情報
 * この値をもとにボートを制御する
 */
USTRUCT(BlueprintType)
struct FInputInfo {
	GENERATED_USTRUCT_BODY()

public:
	FInputInfo() : LeftMotorValue(0.0f), RightMotorValue(0.0f), bBack(false) {
	}
	FInputInfo(float LeftMotorValue, float RightMotorValue, bool bBack)
		: LeftMotorValue(LeftMotorValue), RightMotorValue(RightMotorValue), bBack(bBack) {
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputInfo")
	float LeftMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputInfo")
	float RightMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputInfo")
	bool bBack;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UDriver : public UInterface {
	GENERATED_BODY()
};

/**
 *
 */
class GFF_08_API IDriver {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * 現在の移動入力を取得する
	 * 複数回同一フレームで呼ばれることを考慮し、取得と更新処理を分割
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Driver")
	FInputInfo CurrentInputInfo() const;

	/**
	 * 入力状態を更新する
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Driver")
	void UpdateInputInfo();
};
