// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gff_08/field/CheckPoint.h"

#include "CheckPointManager.generated.h"

UCLASS()
class GFF_08_API ACheckPointManager : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckPointManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CheckPointManager")
	ACheckPoint* GetNextPoint(int32 CurrentIndex) const;
	UFUNCTION(BlueprintCallable, Category = "CheckPointManager")
	ACheckPoint* GetStartPoint() const;

	UFUNCTION(BlueprintCallable, Category = "CheckPointManager")
	void CollectCheckPointsInWorld();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CheckPointManager") TMap<int32, ACheckPoint*> CheckPoints;
};
