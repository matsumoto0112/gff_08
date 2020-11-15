// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceManager.h"

#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/NetworkConnectUtility.h"
#include "kismet/GamePlayStatics.h"

#include <StrixBlueprintFunctionLibrary.h>

const FName ARaceManager::NEXT_LEVEL_NAME = TEXT("Result");

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

	bRaceStarted = false;

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
	if (UStrixBlueprintFunctionLibrary::IsMasterServerConnected(GWorld) == true) {
		// StrixCloudでバグが起きないようネットワークのポーズを解除する
		//参照:https://www.strixengine.com/doc/unreal/guide/ja/howtos/object_sync/howto_scene_change.html
		UStrixBlueprintFunctionLibrary::UnpauseNetworkObjectManager(
			GWorld, UMyGameInstance::GetInstance()->GetUserData()->GetChannelID());

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, "Connected MasterServer");
		const int32 BoatIndex = UMyGameInstance::GetInstance()->GetUserData()->GetBoatIndex();
		const int32 PlayerIndex = UMyGameInstance::GetInstance()->GetUserData()->GetPlayerIndex();
		const FName PlayerName = UMyGameInstance::GetInstance()->GetUserData()->GetPlayerName();
		MultiRaceSetup(FRacerInfo{PlayerName, PlayerIndex, BoatIndex, ERacerType::Player});

	} else {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, "No Connected MasterServer");
		//シングルプレイ用設定
		FAllRacerInfo Racers;
		Racers.Racers.Push(FRacerInfo{TEXT("Player"), 0, 0, ERacerType::Player});
		Racers.Racers.Push(FRacerInfo{TEXT("AI_1"), 1, 2, ERacerType::AI});
		Racers.Racers.Push(FRacerInfo{TEXT("AI_2"), 2, 3, ERacerType::AI});
		Racers.Racers.Push(FRacerInfo{TEXT("AI_3"), 3, 1, ERacerType::AI});

		RaceSetup(Racers);

		RaceStart();
	}

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
		if (!IsAnyBoatGoaled()) {
			return;
		}
		RaceEndRemainTime -= DeltaTime;
		if (!bRaceEnded && RaceEndRemainTime <= 0.0f) {
			FAllRacersGamePlayData Data;
			if (!UNetworkConnectUtility::IsMultiGame(GetWorld())) {
				Data.MyBoatIndex = 0;
			}

			for (int32 i = 0; i < Boats.Num(); i++) {
				const auto& Boat = Boats[i];
				const FName Name = Boat->GetRacerName();
				const int32 Ranking = Boat->GetLapCounter()->GetRanking();
				const TArray<float> LapTimes = Boat->GetLapCounter()->GetLapTimes();
				Data.AllRacersData.Emplace(Name, Ranking, LapTimes);
				if (UNetworkConnectUtility::IsMultiGame(GetWorld()) && UNetworkConnectUtility::IsOwner(Boat)) {
					Data.MyBoatIndex = i;
				}
			}
			UMyGameInstance::GetInstance()->SetPlayData(Data);
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

void ARaceManager::MultiRaceSetup(const FRacerInfo& Info) {
	Boats.Push(Setup->SetupRacer(Info));
	if (Boats.Num() >= 4) {
		bRaceAlreadySetup = true;
	}
}

void ARaceManager::ReplicateRaceSetup(ABoat* Boat) {
	Boats.Push(Boat);
	if (Boats.Num() >= 4) {
		bRaceAlreadySetup = true;
	}
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
}

URaceTimer* ARaceManager::GetRaceTimer() const {
	return MainUI->GetRaceInfo()->GetRaceTimer();
}

void ARaceManager::CountdownUpdate() {
	CountDownTime -= GetWorld()->GetDeltaSeconds();

	CountDownUI->SetCountDownImage(CountDownTime + 1);
	if (CountDownTime <= 0.0f) {
		CountDownUI->RemoveFromParent();

		for (auto&& Boat : Boats) {
			Boat->RaceStart();
		}
		MainUI->GetRaceInfo()->GetRaceTimer()->Start();
		bRaceStarted = true;
	}
}

bool ARaceManager::IsAnyBoatGoaled() const {
	//周回数を3周として決め打つ
	// TODO:現在のステージ情報から読み取る
	constexpr int32 LAP_END_NUM = 4;
	for (auto&& Boat : Boats) {
		if (Boat->GetLapCounter()->GetLapCount() == LAP_END_NUM) {
			return true;
		}
	}
	return false;
}
