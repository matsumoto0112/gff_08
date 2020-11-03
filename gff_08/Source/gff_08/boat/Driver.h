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
	FInputInfo() : LeftMotorValue(0.0f), RightMotorValue(0.0f) {
	}
	FInputInfo(float LeftMotorValue, float RightMotorValue) : LeftMotorValue(LeftMotorValue), RightMotorValue(RightMotorValue) {
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputInfo")
	float LeftMotorValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputInfo")
	float RightMotorValue;
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Driver")
	FInputInfo CurrentInputInfo() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Driver")
	void UpdateInputInfo();
};
