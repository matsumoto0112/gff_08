// Fill out your copyright notice in the Description page of Project Settings.

#include "LapCounter.h"

#include "gff_08/stage/RaceManager.h"
#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/NetworkConnectUtility.h"
#include "kismet/GamePlayStatics.h"

#include <numeric>

namespace {
/**
 * この周回での時間を取得する
 */
float GetLapTime(float Time, const TArray<float>& LapTimes) {
	//今までのゲーム時間から前回までのラップタイムの合計値を引くことで、今回のラップタイムを計算する
	return Time - std::accumulate(LapTimes.begin(), LapTimes.end(), 0.0f);
}
}	 // namespace

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

	AActor* RaceManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ARaceManager::StaticClass());
	RaceManager = Cast<ARaceManager>(RaceManagerActor);
}

// Called every frame
void ULapCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// チェックポイントを通過した
void ULapCounter::PassCheckPoint(ACheckPoint* PassedCheckPoint) {
	const int32 PassedCheckPointIndex = PassedCheckPoint->GetIndex();
	constexpr int32 START_CHECKPOINT_INDEX = 0;

	auto PlayLapIncrementSound = [](int32 NextLapCount) {
		ESoundResourceType Sound = NextLapCount == 4 ? ESoundResourceType::SE_RACE_GOAL : ESoundResourceType::SE_RACE_LAP_COUNT;
		UMyGameInstance::GetInstance()->GetSoundSystem()->PlaySound2D(Sound);
	};

	// スタート地点のチェックポイント
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// 今までに進んだ最大のチェックポイントがコースの最後のインデックスなら1週してきたということ
		if (MostAdvancedIndex == MaxCheckPointIndex) {
			MostAdcancedLapCount++;

			//現在の時間から今回のラップタイムを取得し、ラップタイムに追加する
			float Time = RaceManager->GetRaceTimer()->GetCurrentTime();
			LapTimes.Add(GetLapTime(Time, LapTimes));
			MostAdvancedIndex = PassedCheckPointIndex;

			AActor* ParentActor = GetOwner();
			if (UNetworkConnectUtility::IsMultiGame(GetWorld())) {
				if (UNetworkConnectUtility::IsOwner(ParentActor)) {
					PlayLapIncrementSound(MostAdcancedLapCount);
				}
			} else {
				if (Cast<ABoat>(ParentActor)->GetPlayerIndex_() == 0) {
					PlayLapIncrementSound(MostAdcancedLapCount);
				}
			}
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
			CurrentLapCount = FMath::Max(CurrentLapCount - 1, 0);
		}
	}
	CurrentIndex = PassedCheckPointIndex;
}

TArray<float> ULapCounter::GetLapTimes() const {
	return LapTimes;
}
