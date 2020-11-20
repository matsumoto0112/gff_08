// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiWaitRoomManager.h"

#include <StrixBlueprintFunctionLibrary.h>

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
	//���[�������o�[�ۑ��p�z�񏉊���
	RoomMemberProperties.Init(FStrixRoomMember(), MAX_ROOM_MEMBER);

}

void AMultiWaitRoomManager::SetCurrentRoomMembers() {
	//���݂̃��[�������o�[���擾
	TArray<FStrixRoomMember> currentRoomMembers = UStrixBlueprintFunctionLibrary::GetCurrentRoomMembers(GWorld, ChannelID);
	bool result = false;
	int32 playerIndex = -1;
	TArray<int32> playerIndexArray;
	int32 i = 0;
	playerIndexArray.Init(-1, MAX_ROOM_MEMBER);
	for (i = 0; i < currentRoomMembers.Num(); i++) {
		UStrixBlueprintFunctionLibrary::TryGetIntProperty(currentRoomMembers[i].Properties, "PlayerIndex", result, playerIndex);
		if (result == false) {
			continue;
		}
		//PlayerIndex�̏��Ԃɏ����i�[����
		RoomMemberProperties[playerIndex] = currentRoomMembers[i];
		playerIndexArray[playerIndex] = playerIndex;
	}

	//���[�����̍X�V
	//�������炢�Ȃ��Ȃ��Ă���l������Ȃ�����������
	for (i = 0; i < RoomMemberProperties.Num(); i++) {
		if (i != playerIndexArray[i]) {
			continue;
		}
		RoomMemberProperties[i] = FStrixRoomMember();
	}
}
