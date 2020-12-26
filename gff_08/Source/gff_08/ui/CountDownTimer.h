// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "CountDownTimer.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API UCountDownTimer : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CountDownTimer")
	void SetCountDownImage(int32 Time);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CountDownTimer")
	void SetStartUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CountDownTimer")
	void SetGoalUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CountDownTimer")
	void SetAnyBoatGoaledUI(int32 RemainSeconds);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CountDownTimer")
	void ClearUI();
};
