// Fill out your copyright notice in the Description page of Project Settings.

#include "RankingCalculator.h"

#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
URankingCalculator::URankingCalculator() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URankingCalculator::BeginPlay() {
	Super::BeginPlay();
}

void URankingCalculator::Setup(const TArray<ABoat*>& InBoats) {
	this->Boats.Empty();
	this->Boats = InBoats;
	AActor* ManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACheckPointManager::StaticClass());
	CheckPointManager = Cast<ACheckPointManager>(ManagerActor);
}

// Called every frame
void URankingCalculator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//ボートをルールによってソートし、順位を設定する
	Boats.Sort([&](const ABoat& A, const ABoat& B) {
		const int32 LapCount_A = A.GetLapCounter()->GetLapCount();
		const int32 LapCount_B = B.GetLapCounter()->GetLapCount();
		// ラップ数での降順
		if (LapCount_A != LapCount_B) {
			return LapCount_A > LapCount_B;
		}

		const int32 CheckPointIndex_A = A.GetLapCounter()->GetCurrentCheckPointIndex();
		const int32 CheckPointIndex_B = B.GetLapCounter()->GetCurrentCheckPointIndex();
		// チェックポイントインデックスでの降順
		if (CheckPointIndex_A != CheckPointIndex_B) {
			return CheckPointIndex_A > CheckPointIndex_B;
		}

		//チェックポイントまでの距離順で最終決定
		const ACheckPoint* CheckPoint_A = CheckPointManager->GetNextPoint(CheckPointIndex_A);
		const float Distance_A_NextCheckPoint = FVector::Distance(CheckPoint_A->GetActorLocation(), A.GetActorLocation());

		const ACheckPoint* CheckPoint_B = CheckPointManager->GetNextPoint(CheckPointIndex_B);
		const float Distance_B_NextCheckPoint = FVector::Distance(CheckPoint_B->GetActorLocation(), B.GetActorLocation());

		return Distance_A_NextCheckPoint < Distance_B_NextCheckPoint;
	});

	for (int32 i = 0; i < Boats.Num(); i++) {
		Cast<ABoat>(Boats[i])->GetLapCounter()->SetRanking(i + 1);
	}
}
