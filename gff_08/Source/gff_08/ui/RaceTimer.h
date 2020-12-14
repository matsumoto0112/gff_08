// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "gff_08/ui/UITime.h"

#include "RaceTimer.generated.h"

/**
 * レースの時間計測・表示機能
 */
UCLASS()
class GFF_08_API URaceTimer : public UUserWidget {
	GENERATED_BODY()
protected:
public:
	/**
	 * Tick処理
	 */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	/**
	 * 計測開始
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceTimer")
	void Start();
	/**
	 * 計測終了
	 */
	UFUNCTION(BlueprintCallable, Category = "RaceTimer")
	void Stop();

	UFUNCTION(BlueprintCallable, Category = "RaceTimer")
	void StopUpdateImages();

	/**
	 * 現在の時間を取得する
	 */
	UFUNCTION(BlueprintGetter, Category = "RaceTimer")
	float GetCurrentTime() const {
		return CurrentTime;
	}

protected:
	//! 現在の時間
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCurrentTime, Category = "RaceTimer")
	float CurrentTime;
	//! 計測開始しているか
	UPROPERTY()
	bool bIsStarted = false;
	UPROPERTY()
	bool bUpdateImagesFlag = true;
};
