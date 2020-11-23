// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkConnect.h"

#include "gff_08/utils/MyGameInstance.h"

#include <Adapter\StrixPropertyMap.h>
#include <StrixBlueprintFunctionLibrary.h>

using StrixUtil = UStrixBlueprintFunctionLibrary;

// Sets default values
ANetworkConnect::ANetworkConnect() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
	if (StrixUtil::IsMasterServerConnected(GetWorld()) == false) {
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
	auto instance = UMyGameInstance::GetInstance();
	instance->GetNetworkData()->SetStringMemberProperty("name", name);
	instance->GetNetworkData()->SetBoolMemberProperty("IsStart", false);
	instance->GetNetworkData()->SetIntMemberProperty("PlayerIndex", 0);
	instance->GetNetworkData()->SetIntMemberProperty("BoatIndex", 0);
}

void ANetworkConnect::InitializeRoomProperty(const int32 capacity, const FString roomName) {
	UMyGameInstance::GetInstance()->GetNetworkData()->SetIntRoomProperty("capacity", capacity);
	UMyGameInstance::GetInstance()->GetNetworkData()->SetStringRoomProperty("name", roomName);
}

void ANetworkConnect::UpdateMemberProperty(const int32 channelID) {
	auto instance = UMyGameInstance::GetInstance();

	//チャンネルIDをセット
	instance->GetUserData()->SetChannelID(channelID);
	FStrixRoomMember roomMember = StrixUtil::GetCurrentRoomMember(GetWorld(), channelID);
	// IDと名前をセット
	instance->GetUserData()->SetPlayerID(roomMember.Id);
	instance->GetUserData()->SetPlayerName(*roomMember.Name);

	SetPlayerIndex(StrixUtil::GetCurrentRoom(GetWorld(), channelID).MemberCount, channelID);
	//ポーズ処理
	StrixUtil::PauseNetworkObjectManager(GetWorld(), channelID);
}

void ANetworkConnect::SetPlayerIndex(const int32 memberCount, const int32 channelID) {
	int32 count = memberCount;
	int32 playerIndex = 0;
	auto instance = UMyGameInstance::GetInstance();
	//参加者が一人なら
	if (count == 1) {
		instance->GetUserData()->SetPlayerIndex(playerIndex);
		instance->GetNetworkData()->SetIntMemberProperty("PlayerIndex", playerIndex);
		return;
	}

	//自分のデータを取得
	FStrixRoomMember myUserData = StrixUtil::GetCurrentRoomMember(GetWorld(), channelID);
	//ルーム内のユーザー情報を取得
	TArray<FStrixRoomMember> roomMembers = StrixUtil::GetCurrentRoomMembers(GetWorld(), channelID);
	int32 memberIndex = 0;
	bool result = false;
	for (int i = 0; i < roomMembers.Num(); i++) {
		//自分自身を調べようとしてるなら
		if (myUserData.Id == roomMembers[i].Id) {
			continue;
		}
		//相手のプレイヤー番号を取得する
		StrixUtil::TryGetIntProperty(roomMembers[i].Properties, "PlayerIndex", result, memberIndex);
		//失敗したかどうか
		if (result == false) {
			continue;
		}
		if (memberIndex <= playerIndex) {
			playerIndex++;
		}
	}

	instance->GetUserData()->SetPlayerIndex(playerIndex);
	instance->GetNetworkData()->SetIntMemberProperty("PlayerIndex", playerIndex);
}
