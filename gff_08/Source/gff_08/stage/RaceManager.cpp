// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceManager.h"

#include "kismet/GamePlayStatics.h"

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

	//シングルプレイ用設定
	FAllRacerInfo Racers;
	Racers.Racers.Push(FRacerInfo{0, 0, ERacerType::Player});
	Racers.Racers.Push(FRacerInfo{1, 2, ERacerType::AI});
	Racers.Racers.Push(FRacerInfo{2, 3, ERacerType::AI});
	Racers.Racers.Push(FRacerInfo{3, 1, ERacerType::AI});

	RaceSetup(Racers);
	RaceStart();
}

// Called every frame
void ARaceManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	CountDownTime -= DeltaTime;

	CountDownUI->SetCountDownImage(CountDownTime + 1);
	if (CountDownTime <= 0.0f) {
		CountDownUI->RemoveFromParent();

		for (auto&& Boat : Boats) {
			Boat->RaceStart();
		}
	}
}

void ARaceManager::RaceSetup(const FAllRacerInfo& RacersInfo) {
	Boats = Setup->Setup(RacersInfo);
}

void ARaceManager::RaceStart() {
	if (Boats.Num() == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("RaceStart must be called after Setup Function!!"));
		UE_LOG(LogTemp, Error, TEXT("RaceStart must be called after Setup Function!!"));
		return;
	}
	ACheckPoint* StartPoint = CheckPointManager->GetStartPoint();
	for (auto&& Boat : Boats) {
		Boat->RaceReady(StartPoint);
	}
}
