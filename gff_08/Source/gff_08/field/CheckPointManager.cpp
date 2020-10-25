// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckPointManager.h"

#include <Kismet/GameplayStatics.h>

// Sets default values
ACheckPointManager::ACheckPointManager() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACheckPointManager::BeginPlay() {
	Super::BeginPlay();

	TArray<AActor*> CheckPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckPoint::StaticClass(), CheckPointActors);

	for (auto* Actor : CheckPointActors) {
		if (ACheckPoint* CheckPoint = Cast<ACheckPoint>(Actor)) {
			CheckPoints.Add(CheckPoint->GetIndex(), CheckPoint);
		}
	}
}

// Called every frame
void ACheckPointManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

ACheckPoint* ACheckPointManager::GetNextPoint(int32 CurrentIndex) const {
	int32 NextIndex = (CurrentIndex + 1) % CheckPoints.Num();
	return *CheckPoints.Find(NextIndex);
}
