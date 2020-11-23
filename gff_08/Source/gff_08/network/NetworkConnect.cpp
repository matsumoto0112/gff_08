// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkConnect.h"

#include "gff_08/utils/MyGameInstance.h"

#include <Adapter\StrixPropertyMap.h>
#include <StrixBlueprintFunctionLibrary.h>

// Sets default values
ANetworkConnect::ANetworkConnect() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANetworkConnect::BeginPlay() {
	Super::BeginPlay();
	IsPressConnectButton = false;
}

// Called every frame
void ANetworkConnect::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ANetworkConnect::ConnectToRandomRoom(const FString name) {
	if (UStrixBlueprintFunctionLibrary::IsMasterServerConnected(GetWorld()) == false) {
		return;
	}

	if (IsPressConnectButton == true) {
		return;
	}

	IsPressConnectButton = true;
}
