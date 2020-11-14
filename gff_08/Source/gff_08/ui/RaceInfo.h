// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "gff_08/ui/RaceTimer.h"

#include "RaceInfo.generated.h"

/**
 * ���[�X���\���pUI
 */
UCLASS()
class GFF_08_API URaceInfo : public UUserWidget {
	GENERATED_BODY()

public:
	/**
	 * ���[�X���ԕ\��UI�̎擾
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "RaceInfo")
	URaceTimer* GetRaceTimer() const;
};
