// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "StageCreateUtils.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API UStageCreateUtils : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "StageCreateUtils")
	static void SetStraightBuoy(AActor* Wall, TSubclassOf<AActor> BuoyClass);

	UFUNCTION(BlueprintCallable, Category = "StageCreateUtils")
	static void SetArchBuoy(AActor* Arch, TSubclassOf<AActor> BuoyClass);
};
