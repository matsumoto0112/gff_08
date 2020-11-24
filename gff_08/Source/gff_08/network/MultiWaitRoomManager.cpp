// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiWaitRoomManager.h"

#include <StrixBlueprintFunctionLibrary.h>
#include "gff_08/utils/MyGameInstance.h"

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

void AMultiWaitRoomManager::Initialize() {
	Timer = 0.0f;
	//���[�������o�[�ۑ��p�z�񏉊���
	RoomMemberProperties.Init(FStrixRoomMember(), MAX_ROOM_MEMBER);
}

void AMultiWaitRoomManager::SetCurrentRoomMembers() {
	int32 channelID = UMyGameInstance::GetInstance()->GetNetworkData()->GetChannelID();
	//���݂̃��[�������o�[���擾
	TArray<FStrixRoomMember> currentRoomMembers = StrixUtil::GetCurrentRoomMembers(GWorld, channelID);
	// PlayerIndex�擾�p
	bool result = false;
	int32 playerIndex = -1;
	TArray<int32> playerIDArray;
	int32 i = 0;
	playerIDArray.Init(-1, MAX_ROOM_MEMBER);
	GEngine->AddOnScreenDebugMessage(
		-1, 3.0f, FColor::Green, FString::Printf(TEXT("Now Length: %d"), currentRoomMembers.Num()), false);
	for (i = 0; i < currentRoomMembers.Num(); i++) {
		StrixUtil::TryGetIntProperty(currentRoomMembers[i].Properties, "PlayerIndex", result, playerIndex);

		if (result == false) {
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Oh...")), false);
			continue;
		}
		// PlayerIndex�̏��Ԃɏ����i�[����
		RoomMemberProperties[playerIndex] = currentRoomMembers[i];
		playerIDArray[playerIndex] = RoomMemberProperties[playerIndex].Id;
	}

	//���[�����̍X�V
	//�������炢�Ȃ��Ȃ��Ă���l������Ȃ�����������
	for (i = 0; i < RoomMemberProperties.Num(); i++) {
		if (playerIDArray[i] == RoomMemberProperties[i].Id) {
			continue;
		}
		RoomMemberProperties[i] = FStrixRoomMember();
	}
}