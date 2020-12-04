// Fill out your copyright notice in the Description page of Project Settings.

#include "StageCreateUtils.h"

#include "Components/ArrowComponent.h"
#include "Engine/Engine.h"

void UStageCreateUtils::SetStraightBuoy(AActor* Wall, TSubclassOf<AActor> BouyClass) {
	auto World = Wall->GetWorld();
	if (!World) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Error: WorldObject is null."));
		return;
	}

	TArray<UActorComponent*> WallEndPoints = Wall->GetComponentsByClass(UArrowComponent::StaticClass());
	if (WallEndPoints.Num() != 2) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Error: Can't set bouys because end points can't find."));
		return;
	}


	const FVector Start = Cast<USceneComponent>(WallEndPoints[0])->GetComponentLocation();
	const FVector End = Cast<USceneComponent>(WallEndPoints[1])->GetComponentLocation();

	const FVector Direction = (End - Start).GetSafeNormal();
	const FRotator Rotator = FRotator::ZeroRotator;
	const float Length = FVector::Distance(Start, End);
	constexpr float STEP = 500.0f;
	float Current = 0.0f;
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Format(TEXT("LEN: {0}"), {Length}));

	while (Current + STEP <= Length) {
		AActor* Buoy = World->SpawnActor<AActor>(BouyClass, Start + Direction * Current, Rotator);
		Buoy->SetFolderPath(TEXT("/Buoys"));

		Current += STEP;
	}
}
