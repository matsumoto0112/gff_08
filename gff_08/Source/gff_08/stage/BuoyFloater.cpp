// Fill out your copyright notice in the Description page of Project Settings.

#include "BuoyFloater.h"

#include "kismet/GameplayStatics.h"

// Sets default values
ABuoyFloater::ABuoyFloater() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuoyFloater::BeginPlay() {
	Super::BeginPlay();

	TArray<AActor*> Buoys;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BuoyClass, Buoys);

	Objects.Reserve(Buoys.Num());
	for (auto&& Buoy : Buoys) {
		Objects.Push({Buoy});
	}
}

// Called every frame
void ABuoyFloater::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Time += DeltaTime;

	auto f = [](float T) { return FMath::Sin(T) * 0.5f; };
	auto f2 = [](float T) { return (3.0 * FMath::Sin(T) + 2.0f * FMath::Cos(3.0f * T)) * 0.1f; };

	const float T = f(Time * 0.65f);
	for (auto&& Object : Objects) {
		FRotator Rot = Object.Buoy->GetActorRotation();
		Rot.Pitch = T * 30.0f;
		Object.Buoy->SetActorRotation(Rot);

		FVector Location = Object.Buoy->GetActorLocation();
		float Z = (FMath::Abs(T) - 1.0f) * 20.0f;
		Location.Z = Z;
		Object.Buoy->SetActorLocation(Location);
	}
}
