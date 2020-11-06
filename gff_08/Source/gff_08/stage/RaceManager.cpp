// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceManager.h"

// Sets default values
ARaceManager::ARaceManager() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	RootComponent = DefaultSceneComponent;

	Setup = CreateDefaultSubobject<USetupRacers>(TEXT("SetupRacers"));
	AddOwnedComponent(Setup);
}

// Called when the game starts or when spawned
void ARaceManager::BeginPlay() {
	Super::BeginPlay();

	FAllRacerInfo RacersInfo;
	RacersInfo.Racers.Push(FRacerInfo{0, ERacerType::Player});
	RacersInfo.Racers.Push(FRacerInfo{1, ERacerType::AI});
	Setup->Setup(RacersInfo);
}

// Called every frame
void ARaceManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
