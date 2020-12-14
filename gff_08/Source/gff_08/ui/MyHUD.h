// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "gff_08/ui/RaceInfo.h"

#include "MyHUD.generated.h"

/**
 * HUDŠî’êƒNƒ‰ƒX
 */
UCLASS()
class GFF_08_API UMyHUD : public UUserWidget {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "MyHUD")
	URaceInfo* GetRaceInfo() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "MyHUD")
	void RankingUpdateStop();
};
