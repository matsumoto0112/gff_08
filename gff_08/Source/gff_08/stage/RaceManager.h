// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gff_08/field/CheckPointManager.h"
#include "gff_08/stage/SetupRacers.h"
#include "gff_08/ui/CountDownTimer.h"

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
	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void RaceSetup(const FAllRacerInfo& RacersInfo);

	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void MultiRaceSetup(const FRacerInfo& Info);

	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void ReplicateRaceSetup(ABoat* Boat);

	UFUNCTION(BlueprintCallable, Category = "RaceManager")
	void RaceStart();

	UFUNCTION(BlueprintGetter, Category = "RaceManager")
	bool GetRaceAlreadySetup() const {
		return bRaceAlreadySetup;
	}

protected:
	//! レースのセットアップ処理担当
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USetupRacers* Setup;
	//! チェックポイント管理者
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	ACheckPointManager* CheckPointManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCountDownTimer* CountDownUI;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float CountDownTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<ABoat*> Boats;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRaceAlreadySetup, Category = "RaceManager")
	bool bRaceAlreadySetup;
};
