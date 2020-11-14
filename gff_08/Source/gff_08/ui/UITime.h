// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "UITime.generated.h"

/**
 * ���ԕ\���pUI
 */
UCLASS()
class GFF_08_API UUITime : public UUserWidget {
	GENERATED_BODY()

public:
	/**
	 * float�Ŏ��Ԃ��Z�b�g����
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "UITime")
	void SetTimeFloat(float Time);
};
