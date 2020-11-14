// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "UITime.generated.h"

/**
 * 時間表示用UI
 */
UCLASS()
class GFF_08_API UUITime : public UUserWidget {
	GENERATED_BODY()

public:
	/**
	 * floatで時間をセットする
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "UITime")
	void SetTimeFloat(float Time);
};
