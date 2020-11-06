// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gff_08/stage/SetupRacers.h"

#include "RaceManager.generated.h"

UCLASS()
class GFF_08_API ARaceManager : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARaceManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USetupRacers* Setup;
};
