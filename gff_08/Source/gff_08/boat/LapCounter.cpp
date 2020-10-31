// Fill out your copyright notice in the Description page of Project Settings.

#include "LapCounter.h"

// Sets default values for this component's properties
ULapCounter::ULapCounter() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULapCounter::BeginPlay() {
	Super::BeginPlay();

	MostAdvancedIndex = 0;
	MostAdcancedLapCount = 1;
	CurrentIndex = 0;
	CurrentLapCount = 1;
}

// Called every frame
void ULapCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentLapTime += DeltaTime;
}

// チェックポイントを通過した
void ULapCounter::PassCheckPoint(ACheckPoint* PassedCheckPoint) {
	const int32 PassedCheckPointIndex = PassedCheckPoint->GetIndex();
	constexpr int32 START_CHECKPOINT_INDEX = 0;

	// スタート地点のチェックポイント
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// 今までに進んだ最大のチェックポイントがコースの最後のインデックスなら1週してきたということ
		if (MostAdvancedIndex == MaxCheckPointIndex) {
			MostAdcancedLapCount++;
			LapTimes.Add(CurrentLapTime);
			CurrentLapTime = 0.0f;
			MostAdvancedIndex = PassedCheckPointIndex;
		}

	} else {
		// 次のチェックポイントに触れたらその情報で更新
		if (MostAdvancedIndex + 1 == PassedCheckPointIndex) {
			MostAdvancedIndex = PassedCheckPointIndex;
		}
	}

	// 順位決定用のインデックスの更新処理
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// 周回したタイミングで加算
		if (CurrentIndex == MaxCheckPointIndex) {
			CurrentLapCount++;
		}
	} else if (PassedCheckPointIndex == MaxCheckPointIndex) {
		// 戻ったタイミングで減算
		if (CurrentIndex == START_CHECKPOINT_INDEX) {
			CurrentLapCount = FMath::Max(CurrentLapCount - 1, 1);
		}
	}
	CurrentIndex = PassedCheckPointIndex;
}

float ULapCounter::GetTotalLapTime() const {
	float TotalTime = 0.0f;
	for (auto&& Time : LapTimes) {
		TotalTime += Time;
	}
	return TotalTime;
}
