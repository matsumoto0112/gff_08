// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "gff_08/boat/Driver.h"

#include "AIBrain.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class GFF_08_API UAIBrain : public UObject {
	GENERATED_BODY()

public:
	UAIBrain();

	UFUNCTION(BlueprintCallable, Category = "Brain")
	void Init();

	UFUNCTION(BlueprintCallable, Category = "Brain")
	FInputInfo Next();

private:
};
