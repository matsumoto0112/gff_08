// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "gff_08/boat/Boat.h"
#include "gff_08/boat/Driver.h"

#include "AIBrain.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class GFF_08_API UAIBrain : public UObject, public IDriver {
	GENERATED_BODY()

public:
	UAIBrain();

	UFUNCTION(BlueprintCallable, Category = "Brain")
	void Init(ABoat* Boat);

	FInputInfo Next();
	/**
	 * 現在の移動入力を取得する
	 * 複数回同一フレームで呼ばれることを考慮し、取得と更新処理を分割
	 */
	virtual FInputInfo CurrentInputInfo_Implementation() const override;

	/**
	 * 入力状態を更新する
	 */
	virtual void UpdateInputInfo_Implementation() override;

private:
	void UpdateTargetPoint();

private:
	UPROPERTY()
	ABoat* Parent;
	UPROPERTY()
	FInputInfo InputInfo;
	UPROPERTY()
	FVector CurrentTargetPoint;
	UPROPERTY()
	int32 CurrentTargetCheckPointIndex;
	UPROPERTY()
	int32 Intelligence = 0;
	UPROPERTY()
	float Line;
};
