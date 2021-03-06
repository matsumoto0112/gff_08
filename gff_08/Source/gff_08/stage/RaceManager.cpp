// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceManager.h"

#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/NetworkConnectUtility.h"
#include "kismet/GamePlayStatics.h"

const FName ARaceManager::NEXT_LEVEL_NAME = TEXT("Result");

// Sets default values
ARaceManager::ARaceManager() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	RootComponent = DefaultSceneComponent;

	Setup = CreateDefaultSubobject<USetupRacers>(TEXT("SetupRacers"));
	AddOwnedComponent(Setup);

	RankingCalculator = CreateDefaultSubobject<URankingCalculator>(TEXT("RankingCalculator"));
	AddOwnedComponent(RankingCalculator);
}

// Called when the game starts or when spawned
void ARaceManager::BeginPlay() {
	Super::BeginPlay();

	UMyGameInstance::GetInstance()->GetSoundSystem()->StopBGM();
	bRaceStarted = false;
	bRaceEndCountdownStarted = false;

	const FString Path = "/Game/Blueprints/UI/BP_CountDownTimer.BP_CountDownTimer_C";
	TSubclassOf<UCountDownTimer> WidgetClass = TSoftClassPtr<UCountDownTimer>(FSoftObjectPath(*Path)).LoadSynchronous();
	CountDownUI = CreateWidget<UCountDownTimer>(GetWorld(), WidgetClass);
	if (!CountDownUI) {
		UE_LOG(LogTemp, Error, TEXT("CountDownTimer_UI can not create."));
		return;
	}
	CountDownUI->AddToViewport(1);

	if (!CheckPointManager) {
		UE_LOG(LogTemp, Error, TEXT("CheckPointManager is not set."));
		return;
	}

	bRaceAlreadySetup = false;

	//マルチゲームなら
	if (UNetworkConnectUtility::IsMultiGame(GetWorld()) == true) {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, "Connected MasterServer");

	} else {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, "No Connected MasterServer");
		//シングルプレイ用設定
		const int32 PlayerBoatIndex = UMyGameInstance::GetInstance()->GetUserData()->GetBoatIndex();
		FAllRacerInfo Racers;
		Racers.Racers.Push(FRacerInfo{TEXT("Player"), 0, PlayerBoatIndex, ERacerType::Player});

		Racers.Racers.Push(FRacerInfo{TEXT("AI_1"), 1, FMath::RandRange(0, 3), ERacerType::AI});
		Racers.Racers.Push(FRacerInfo{TEXT("AI_2"), 2, FMath::RandRange(0, 3), ERacerType::AI});
		Racers.Racers.Push(FRacerInfo{TEXT("AI_3"), 3, FMath::RandRange(0, 3), ERacerType::AI});

		RaceSetup(Racers);

		RaceStart();
	}

	//シングルプレイだったらここで大丈夫
	RankingCalculator->Setup(Boats);

	//メインのUIの中ではプレイヤーを参照する必要があるため、Setupの完了後に呼ぶ
	// TODO:MyHUDクラス内にプレイヤーの取得機能を作成し、Setup後に呼ぶようにする
	MainUI = CreateWidget<UMyHUD>(GetWorld(), HUDClass);
	if (!MainUI) {
		UE_LOG(LogTemp, Error, TEXT("MainUI can not create."));
		return;
	}
	MainUI->AddToViewport(0);
}

// Called every frame
void ARaceManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bRaceAlreadySetup)
		return;

	if (bRaceStarted) {
		if (!bRaceEndCountdownStarted) {
			bRaceEndCountdownStarted = IsAnyBoatGoaled();
			return;
		}
		CountDownUI->SetAnyBoatGoaledUI(static_cast<int32>(RaceEndRemainTime));
		RaceEndRemainTime -= DeltaTime;
		if (!bRaceEnded && RaceEndRemainTime <= 0.0f) {
			//マルチプレイ時の終了処理
			if (UNetworkConnectUtility::IsMultiGame(GetWorld())) {
				GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, TEXT("MultiPlay Ended"));
				UE_LOG(LogTemp, Log, TEXT("MultiPlay Ended"));
				//何もしない
			} else {
				GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, TEXT("SinglePlay Ended"));
				UE_LOG(LogTemp, Log, TEXT("SinglePlay Ended"));
				CalculateResult();
			}
			UGameplayStatics::OpenLevel(GetWorld(), NEXT_LEVEL_NAME);
			bRaceEnded = true;
		}
	} else {
		CountdownUpdate();
	}
}

void ARaceManager::RaceSetup(const FAllRacerInfo& RacersInfo) {
	Boats = Setup->Setup(RacersInfo);
	bRaceAlreadySetup = true;
}

ABoat* ARaceManager::SpawnBoat(const FNetworkUserData& UserData) {
	FRacerInfo Info;
	Info.BoatIndex = UserData.BoatIndex;
	Info.PlayerIndex = UserData.PlayerIndex;
	Info.RacerName = UserData.PlayerName;

	const int32 MyPlayerIndex = UMyGameInstance::GetInstance()->GetUserData()->GetPlayerIndex();
	Info.RacerType = MyPlayerIndex == UserData.PlayerIndex ? ERacerType::Player : ERacerType::ReplecatedPlayer;

	ABoat* Res = Setup->SetupRacer(Info);
	Boats.Push(Res);

	return Res;
}

void ARaceManager::MultiRaceSetup(const FRacerInfo& Info) {
	// Boats.Push(Setup->SetupRacer(Info));
	// if (Boats.Num() >= 4) {
	//	bRaceAlreadySetup = true;
	//}
}

void ARaceManager::ReplicateRaceSetup(ABoat* Boat, const int32 BoatIndex, const int32 PlayerIndex) {
	//複製されたボートのプレイヤー番号を0に固定しておく
	// Boat->ChangeBoat(BoatIndex, PlayerIndex);
	// Boats.Push(Boat);
	//// if (Boats.Num() >= 4) {
	//	bRaceAlreadySetup = true;
	//}
}

bool ARaceManager::IsStart() {
	if (Boats.Num() >= 4) {
		// bRaceAlreadySetup = true;
		return true;
	}
	return false;
}

void ARaceManager::StartRaceSetUp() {
	if (bRaceAlreadySetup == true) {
		return;
	}
	bRaceAlreadySetup = true;
	RaceStart();
}

void ARaceManager::RaceStart() {
	if (!bRaceAlreadySetup) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("RaceStart must be called after Setup Function!!"));
		UE_LOG(LogTemp, Error, TEXT("RaceStart must be called after Setup Function!!"));
		return;
	}
	ACheckPoint* StartPoint = CheckPointManager->GetStartPoint();
	for (auto&& Boat : Boats) {
		Boat->RaceReady(StartPoint);
	}

	//マルチプレイ用
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, FString::Format(TEXT("{0} Racers Setup!!"), {Boats.Num()}));
	RankingCalculator->Setup(Boats);
}

URaceTimer* ARaceManager::GetRaceTimer() const {
	return MainUI->GetRaceInfo()->GetRaceTimer();
}

void ARaceManager::TestCallRaceEndEventFunction() {
	RaceEndEvent.Broadcast();
}

void ARaceManager::CountdownUpdate() {
	const float PrevCountDownTime = CountDownTime;
	CountDownTime -= GetWorld()->GetDeltaSeconds();
	if ((int32) CountDownTime != (int32) PrevCountDownTime && (int32) CountDownTime >= 0) {
		UMyGameInstance::GetInstance()->GetSoundSystem()->PlaySound2D(ESoundResourceType::SE_RACE_COUNTDOWN);
	}

	CountDownUI->SetCountDownImage(CountDownTime + 1);
	if (CountDownTime <= 0.0f) {
		CountDownUI->SetStartUI();

		for (auto&& Boat : Boats) {
			Boat->RaceStart();
		}
		MainUI->GetRaceInfo()->GetRaceTimer()->Start();
		bRaceStarted = true;
		UMyGameInstance::GetInstance()->GetSoundSystem()->PlayBGM(ESoundResourceType::BGM_RACE);
		UMyGameInstance::GetInstance()->GetSoundSystem()->PlaySound2D(ESoundResourceType::SE_RACE_START);

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(
			Handle, [&]() { CountDownUI->ClearUI(); }, 3.0f, false);
	}
}

bool ARaceManager::IsAnyBoatGoaled() const {
	//周回数を3周として決め打つ
	// TODO:現在のステージ情報から読み取る
	constexpr int32 LAP_END_NUM = 4;
	for (auto&& Boat : Boats) {
		if (Boat->GetLapCounter()->GetMostAdvancedLapCount() == LAP_END_NUM) {
			return true;
		}
	}
	return false;
}

void ARaceManager::CalculateResult() {
	auto GetData = [&](int32 i) {
		const auto& Boat = Boats[i];
		const FRacerInfo RacerInfo = Boat->GetRacerInfo();
		const int32 PlayerIndex = RacerInfo.PlayerIndex;
		const FName Name = RacerInfo.RacerName;

		// 3周文のデータがたまるまで0埋めする
		TArray<float> LapTimes = Boat->GetLapCounter()->GetLapTimes();
		while (LapTimes.Num() < 3) {
			LapTimes.Push(0.0f);
		}
		return FGamePlayData{PlayerIndex, Name, LapTimes};
	};

	auto Res = UMyGameInstance::GetInstance()->GetPlayData();
	Res->Player1Data = GetData(0);
	Res->Player2Data = GetData(1);
	Res->Player3Data = GetData(2);
	Res->Player4Data = GetData(3);
}
