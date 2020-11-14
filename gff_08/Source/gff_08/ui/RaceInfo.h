// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "gff_08/ui/RaceTimer.h"

#include "RaceInfo.generated.h"

/**
 * レース情報表示用UI
 */
UCLASS()
class GFF_08_API URaceInfo : public UUserWidget {
	GENERATED_BODY()

public:
	/**
	 * レース時間表示UIの取得
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "RaceInfo")
	URaceTimer* GetRaceTimer() const;
};
