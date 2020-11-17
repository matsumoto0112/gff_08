// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckPoint.h"

#include "gff_08/field/CheckPointManager.h"

#include <Kismet/GameplayStatics.h>

// Sets default values
ACheckPoint::ACheckPoint() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay() {
	Super::BeginPlay();

	AActor* ManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACheckPointManager::StaticClass());
	Manager = Cast<ACheckPointManager>(ManagerActor);

	check(Manager);
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

ACheckPoint* ACheckPoint::GetNextPoint() const {
	if (Manager) {
		return Manager->GetNextPoint(Index);
	} else {
		return nullptr;
	}
}

ACheckPoint* ACheckPoint::GetPrevPoint() const {
	if (Manager) {
		return Manager->GetPrevPoint(Index);
	} else {
		return nullptr;
	}
}
