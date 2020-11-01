// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SpeedConverter.generated.h"

/**
 * km/h��cm/s�𑊌ݕϊ����郉�C�u����
 */
UCLASS()
class GFF_08_API USpeedConverter : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	/**
	 * cm/s => km/h
	 */
	UFUNCTION(BlueprintCallable, Category = "SpeedConverter")
	static float ToSpeedKilometerPerHour(float SpeedCentimeterPerSecond);

public:
	/**
	 * km/h => cm/s
	 */
	UFUNCTION(BlueprintCallable, Category = "SpeedConverter")
	static float ToSpeedCentimeterPerSecond(float KilometerPerHour);
};
