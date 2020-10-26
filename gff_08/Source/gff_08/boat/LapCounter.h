// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "gff_08/field/CheckPoint.h"

#include "LapCounter.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GFF_08_API ULapCounter : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULapCounter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "LapCounter")
	void PassCheckPoint(ACheckPoint* PassedCheckPoint);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 LapCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 CurrentCheckPointIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LapCounter")
	int32 MaxCheckPointIndex;
};
