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
	UFUNCTION(BlueprintGetter, Category = "PlayUserData")
	int32 GetPlayerIndex() const {
		return PlayerIndex;
	}
	UFUNCTION(BlueprintSetter, Category = "PlayUserData")
	void SetPlayerIndex(int32 Index) {
		PlayerIndex = Index;
	}
	UFUNCTION(BlueprintGetter, Category = "PlayUserData")
	int32 GetChannelID() const {
		return ChannelID;
	}
	UFUNCTION(BlueprintSetter, Category = "PlayUserData")
	void SetChannelID(int32 ID) {
		ChannelID = ID;
	}


protected:
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetBoatIndex, BlueprintSetter = SetBoatIndex, Category = "PlayUserData")
	int32 BoatIndex;
	UPROPERTY(
		VisibleAnywhere, BlueprintGetter = GetSelectStageIndex, BlueprintSetter = SetSelectStageIndex, Category = "PlayUserData")
	int32 SelectStageIndex;
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetPlayerIndex, BlueprintSetter = SetPlayerIndex, Category = "PlayUserData")
	int32 PlayerIndex;
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetChannelID, BlueprintSetter = SetChannelID, Category = "PlayUserData")
	int32 ChannelID;
};
