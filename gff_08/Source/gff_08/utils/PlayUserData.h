// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "PlayUserData.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API UPlayUserData : public UObject {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintGetter, Category = "PlayUserData")
	int32 GetBoatIndex() const {
		return BoatIndex;
	}
	UFUNCTION(BlueprintSetter, Category = "PlayUserData")
	void SetBoatIndex(int32 Index) {
		BoatIndex = Index;
	}
	UFUNCTION(BlueprintGetter, Category = "PlayUserData")
	int32 GetSelectStageIndex() const {
		return SelectStageIndex;
	}
	UFUNCTION(BlueprintSetter, Category = "PlayUserData")
	void SetSelectStageIndex(int32 Index) {
		SelectStageIndex = Index;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetBoatIndex, BlueprintSetter = SetBoatIndex, Category = "PlayUserData")
	int32 BoatIndex;
	UPROPERTY(
		VisibleAnywhere, BlueprintGetter = GetSelectStageIndex, BlueprintSetter = SetSelectStageIndex, Category = "PlayUserData")
	int32 SelectStageIndex;
};
