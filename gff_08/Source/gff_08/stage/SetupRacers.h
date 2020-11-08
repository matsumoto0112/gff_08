// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "gff_08/boat/Boat.h"
#include "gff_08/utils/RacersInfo.h"

#include "SetupRacers.generated.h"

/**
 * レーサーたちのセットアップを担当する
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GFF_08_API USetupRacers : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USetupRacers();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * レーサーたちをセットアップする
	 * @return レーサーのボートの配列
	 */
	UFUNCTION(BlueprintCallable, Category = "SetUpRacers")
	TArray<ABoat*> Setup(const FAllRacerInfo& RacersInfo);

protected:
	//! 開始地点
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetupRacers")
	TArray<ATargetPoint*> StartPoints;

	//! スポーンするボートのクラス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetupRacers")
	TMap<ERacerType, TSubclassOf<ABoat>> BoatClasses;
};
