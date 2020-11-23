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

bool ANetworkConnect::IsConnectToRoom() {
	//マスターサーバーに接続されていないなら
	if (UStrixBlueprintFunctionLibrary::IsMasterServerConnected(GetWorld()) == false) {
		return false;
	}

	//すでに接続ボタンが押されていたら
	if (IsPressConnectButton == true) {
		return false;
	}

	IsPressConnectButton = true;

	return true;
}

void ANetworkConnect::InitializeMemberProperty(const FString name) {
	UMyGameInstance::GetInstance()->GetNetworkData()->SetStringMemberProperty("name", name);
	UMyGameInstance::GetInstance()->GetNetworkData()->SetBoolMemberProperty("IsStart", false);
	UMyGameInstance::GetInstance()->GetNetworkData()->SetIntMemberProperty("PlayerIndex", 0);
	UMyGameInstance::GetInstance()->GetNetworkData()->SetIntMemberProperty("BoatIndex", 0);
}

void ANetworkConnect::InitializeRoomProperty(const int32 capacity, const FString roomName) {
	UMyGameInstance::GetInstance()->GetNetworkData()->SetIntRoomProperty("capacity", capacity);
	UMyGameInstance::GetInstance()->GetNetworkData()->SetStringRoomProperty("name", roomName);
}

void ANetworkConnect::UpdateMemberProperty(const int32 channelID) {
	UMyGameInstance::GetInstance()->GetUserData()->SetChannelID(channelID);
	FStrixRoomMember roomMember = UStrixBlueprintFunctionLibrary::GetCurrentRoomMember(GetWorld(), channelID);
	UMyGameInstance::GetInstance()->GetUserData()->SetPlayerID(roomMember.Id);
	
	UMyGameInstance::GetInstance()->GetUserData()->SetPlayerName(*roomMember.Name);

	SetPlayerIndex(channelID);
	//ポーズ処理
	UStrixBlueprintFunctionLibrary::PauseNetworkObjectManager(GetWorld(), channelID);
}

void ANetworkConnect::SetPlayerIndex(const int32 channelID) {
	FStrixRoom roomInfo =  UStrixBlueprintFunctionLibrary::GetCurrentRoom(GetWorld(), channelID);
}
