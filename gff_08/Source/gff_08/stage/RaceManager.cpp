// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceManager.h"

#include "../utils/MyGameInstance.h"
#include "kismet/GamePlayStatics.h"

#include <StrixBlueprintFunctionLibrary.h>

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
		int32 BoatIndex = UMyGameInstance::GetInstance()->GetUserData()->GetBoatIndex();
		int32 PlayerIndex = UMyGameInstance::GetInstance()->GetUserData()->GetPlayerIndex();
		MultiRaceSetup(FRacerInfo{PlayerIndex, BoatIndex, ERacerType::Player});
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, "No Connected MasterServer");
		//シングルプレイ用設定
		FAllRacerInfo Racers;
		Racers.Racers.Push(FRacerInfo{0, 0, ERacerType::Player});
		Racers.Racers.Push(FRacerInfo{1, 2, ERacerType::AI});
		Racers.Racers.Push(FRacerInfo{2, 3, ERacerType::AI});
		Racers.Racers.Push(FRacerInfo{3, 1, ERacerType::AI});

		RaceSetup(Racers);

		RaceStart();
	}

	//メインのUIの中ではプレイヤーを参照する必要があるため、Setupの完了後に呼ぶ
	//TODO:MyHUDクラス内にプレイヤーの取得機能を作成し、Setup後に呼ぶようにする
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

	if (bRaceStarted)
		return;

	CountDownTime -= DeltaTime;

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

void ARaceManager::ReplicateRaceSetup(ABoat* Boat,const int32 BoatIndex) {
	Boat->ChangeBoat(BoatIndex);
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
