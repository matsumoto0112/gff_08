// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BuoyFloater.generated.h"

USTRUCT()
struct FFloaterObjectParams {
	GENERATED_BODY()

	AActor* Buoy;
};

UCLASS()
class GFF_08_API ABuoyFloater : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuoyFloater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BoatFloater")
	TSubclassOf<AActor> BuoyClass;

private:
	float Time;
	UPROPERTY()
	TArray<FFloaterObjectParams> Objects;
};
