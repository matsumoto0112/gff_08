// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiWaitRoomManager.h"

#include <StrixBlueprintFunctionLibrary.h>

using StrixUtil = UStrixBlueprintFunctionLibrary;

// Sets default values
AMultiWaitRoomManager::AMultiWaitRoomManager() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMultiWaitRoomManager::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AMultiWaitRoomManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	Timer += DeltaTime;
	if (Timer < LIMIT_TIME) {
		return;
	}
	SetCurrentRoomMembers();
	Timer = 0.0f;
}

void AMultiWaitRoomManager::Initialize(int32 ID) {
	ChannelID = ID;
	Timer = 0.0f;
	//ルームメンバー保存用配列初期化
	RoomMemberProperties.Init(FStrixRoomMember(), MAX_ROOM_MEMBER);
}

void AMultiWaitRoomManager::SetCurrentRoomMembers() {
	//現在のルームメンバー情報取得
	TArray<FStrixRoomMember> currentRoomMembers = StrixUtil::GetCurrentRoomMembers(GWorld, ChannelID);
	// PlayerIndex取得用
	bool result = false;
	int32 playerIndex = -1;
	TArray<int32> playerIDArray;
	int32 i = 0;
	playerIDArray.Init(-1, MAX_ROOM_MEMBER);
	GEngine->AddOnScreenDebugMessage(
		-1, 3.0f, FColor::Green, FString::Printf(TEXT("Now Length: %d"), currentRoomMembers.Num()), false);
	for (i = 0; i < currentRoomMembers.Num(); i++) {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, currentRoomMembers[i].Name, false);
		StrixUtil::TryGetIntProperty(currentRoomMembers[i].Properties, "BoatIndex", result, playerIndex);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("BoatIndex: %d"), playerIndex), false);
		StrixUtil::TryGetIntProperty(currentRoomMembers[i].Properties, "PlayerIndex", result, playerIndex);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("PlayerIndex: %d"), playerIndex), false);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, "---------------------------", false);

		if (result == false) {
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Oh...")), false);
			continue;
		}
		// playerIndexの番号時のIDと一致しているなら
		if (RoomMemberProperties[playerIndex].Id == currentRoomMembers[i].Id) {
			playerIDArray[playerIndex] = RoomMemberProperties[playerIndex].Id;
			continue;
		}
		// PlayerIndexの順番に情報を格納する
		RoomMemberProperties[playerIndex] = currentRoomMembers[i];
		playerIDArray[playerIndex] = RoomMemberProperties[playerIndex].Id;
	}

	//ルーム情報の更新
	//部屋からいなくなっている人がいるなら空情報を代入する
	for (i = 0; i < RoomMemberProperties.Num(); i++) {
		if (playerIDArray[i] == RoomMemberProperties[i].Id) {
			continue;
		}
		RoomMemberProperties[i] = FStrixRoomMember();
	}
}
