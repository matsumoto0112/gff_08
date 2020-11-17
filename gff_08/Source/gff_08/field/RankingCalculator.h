// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "gff_08/boat/Boat.h"
#include "gff_08/boat/LapCounter.h"
#include "gff_08/field/CheckPointManager.h"

#include "RankingCalculator.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GFF_08_API URankingCalculator : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URankingCalculator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void Setup(const TArray<ABoat*>& InBoats);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RankingCalculator")
	TSubclassOf<APawn> BoatClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RankingCalculator")
	TArray<ABoat*> Boats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RankingCalculator")
	ACheckPointManager* CheckPointManager;
};
