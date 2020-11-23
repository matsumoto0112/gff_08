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
	//�}�X�^�[�T�[�o�[�ɐڑ�����Ă��Ȃ��Ȃ�
	if (StrixUtil::IsMasterServerConnected(GetWorld()) == false) {
		return false;
	}

	//���łɐڑ��{�^����������Ă�����
	if (IsPressConnectButton == true) {
		return false;
	}

	IsPressConnectButton = true;

	return true;
}

void ANetworkConnect::InitializeMemberProperty(const FString name) {
	auto instance = UMyGameInstance::GetInstance();
	FStrixPropertyMap memberProperties;
	memberProperties = instance->GetNetworkData()->SetStringMemberProperty(memberProperties, "name", name);
	memberProperties = instance->GetNetworkData()->SetBoolMemberProperty(memberProperties, "IsStart", false);
	memberProperties = instance->GetNetworkData()->SetIntMemberProperty(memberProperties, "PlayerIndex", 0);
	memberProperties = instance->GetNetworkData()->SetIntMemberProperty(memberProperties, "BoatIndex", 0);
	instance->GetNetworkData()->SetMemberProperties(memberProperties);
}

void ANetworkConnect::InitializeRoomProperty(const int32 capacity, const FString roomName) {
	FStrixPropertyMap roomProperties;
	roomProperties = UMyGameInstance::GetInstance()->GetNetworkData()->SetIntRoomProperty(roomProperties, "capacity", capacity);
	roomProperties = UMyGameInstance::GetInstance()->GetNetworkData()->SetStringRoomProperty(roomProperties, "name", roomName);
	UMyGameInstance::GetInstance()->GetNetworkData()->SetRoomProperties(roomProperties);
}

void ANetworkConnect::UpdateMemberProperty(const int32 channelID) {
	auto instance = UMyGameInstance::GetInstance();

	//�`�����l��ID���Z�b�g
	instance->GetUserData()->SetChannelID(channelID);
	instance->GetNetworkData()->SetChannelID(channelID);
	FStrixRoomMember roomMember = StrixUtil::GetCurrentRoomMember(GetWorld(), channelID);
	// ID�Ɩ��O���Z�b�g
	instance->GetUserData()->SetPlayerID(roomMember.Id);
	instance->GetUserData()->SetPlayerName(*roomMember.Name);

	SetPlayerIndex(StrixUtil::GetCurrentRoom(GetWorld(), channelID).MemberCount, channelID);
	//�|�[�Y����
	StrixUtil::PauseNetworkObjectManager(GetWorld(), channelID);
}

void ANetworkConnect::SetPlayerIndex(const int32 memberCount, const int32 channelID) {
	int32 count = memberCount;
	int32 playerIndex = 0;
	auto instance = UMyGameInstance::GetInstance();

	//�Q���҂���l�Ȃ�
	if (count == 1) {
		instance->GetUserData()->SetPlayerIndex(playerIndex);
		instance->GetNetworkData()->SetMemberProperties(instance->GetNetworkData()->SetIntMemberProperty(
			instance->GetNetworkData()->GetMemberProperties(), "PlayerIndex", playerIndex));
		return;
	}

	//�����̃f�[�^���擾
	FStrixRoomMember myUserData = StrixUtil::GetCurrentRoomMember(GetWorld(), channelID);
	//���[�����̃��[�U�[�����擾
	TArray<FStrixRoomMember> roomMembers = StrixUtil::GetCurrentRoomMembers(GetWorld(), channelID);
	int32 memberIndex = 0;
	bool result = false;
	for (int i = 0; i < roomMembers.Num(); i++) {
		//�������g�𒲂ׂ悤�Ƃ��Ă�Ȃ�
		if (myUserData.Id == roomMembers[i].Id) {
			continue;
		}
		//����̃v���C���[�ԍ����擾����
		StrixUtil::TryGetIntProperty(roomMembers[i].Properties, "PlayerIndex", result, memberIndex);
		//���s�������ǂ���
		if (result == false) {
			continue;
		}
		if (memberIndex <= playerIndex) {
			playerIndex++;
		}
	}

	instance->GetUserData()->SetPlayerIndex(playerIndex);
	instance->GetNetworkData()->SetMemberProperties(instance->GetNetworkData()->SetIntMemberProperty(
		instance->GetNetworkData()->GetMemberProperties(), "PlayerIndex", playerIndex));
}
