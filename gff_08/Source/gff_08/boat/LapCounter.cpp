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
	MostAdvancedLapCount = 1;
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

	//周回時の音を再生する
	auto PlayLapIncrementSound = [&](int32 NextLapCount) {
		USoundSystem* SoundSystem = UMyGameInstance::GetInstance()->GetSoundSystem();
		switch (NextLapCount) {
			case 2:	   // 1週目終了 2週目開始時
				SoundSystem->PlaySound2D(ESoundResourceType::SE_RACE_LAP_COUNT);
				break;
			case 3:	   // 2週目終了 3週目開始時
				SoundSystem->PlaySound2D(ESoundResourceType::SE_RACE_LAP_COUNT);
				SoundSystem->ChangeBGMPitchPattern(BGMPitchPattern::Fast);
				break;
			case 4:	   // 3週目終了 ゴール後
			{
				SoundSystem->PlaySound2D(ESoundResourceType::SE_RACE_GOAL);
				SoundSystem->PlayBGM(ESoundResourceType::BGM_GOAL);
				RaceManager->GetHUD()->RankingUpdateStop();
				AActor* ParentActor = GetOwner();
				ABoat* ParentBoat = Cast<ABoat>(ParentActor);
				ParentBoat->EnableAutoMode();
			} break;
			default:
				break;
		}
	};

	// スタート地点のチェックポイント
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// 今までに進んだ最大のチェックポイントがコースの最後のインデックスなら1週してきたということ
		if (PassedCheckPoint->IsLastCheckPointIndex(MostAdvancedIndex)) {
			MostAdvancedLapCount++;

			//現在の時間から今回のラップタイムを取得し、ラップタイムに追加する
			const float Time = RaceManager->GetRaceTimer()->GetCurrentTime();
			LapTimes.Add(GetLapTime(Time, LapTimes));
			MostAdvancedIndex = PassedCheckPointIndex;

			AActor* ParentActor = GetOwner();
			ABoat* ParentBoat = Cast<ABoat>(ParentActor);

			//マルチ接続時なら自分がオーナーの時に音を再生する
			if (UNetworkConnectUtility::IsOwnerPlayerIndex(ParentBoat->GetRacerInfo().PlayerIndex)) {
				PlayLapIncrementSound(MostAdvancedLapCount);
			}

			LapIncrementDispatcher.Broadcast(MostAdvancedLapCount);
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
		//直前までにいたインデックスがこのステージ中最後のチェックポイントのインデックスなら周回してきたということ
		if (PassedCheckPoint->IsLastCheckPointIndex(CurrentIndex)) {
			CurrentLapCount++;
		}
		// 戻ったタイミングで減算
		if (CurrentIndex == START_CHECKPOINT_INDEX + 1) {
			CurrentLapCount = FMath::Max(CurrentLapCount - 1, 0);
		}
	}
	CurrentIndex = PassedCheckPointIndex;
}

TArray<float> ULapCounter::GetLapTimes() const {
	return LapTimes;
}
