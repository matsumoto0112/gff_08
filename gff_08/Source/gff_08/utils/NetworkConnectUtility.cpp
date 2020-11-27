// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkConnectUtility.h"

#include "gff_08/utils/MyGameInstance.h"

bool UNetworkConnectUtility::IsOwner(const AActor* target) {
	if (target != nullptr) {
		UStrixReplicatorComponent* replicator = target->FindComponentByClass<UStrixReplicatorComponent>();
		if (replicator == nullptr) {
			return false;
		}
		return replicator->GetIsOwner();
	}
	return false;
}

bool UNetworkConnectUtility::IsMultiGame(const UObject* worldContextObject) {
	return IsMasterServerConnected(worldContextObject);
}

bool UNetworkConnectUtility::IsOwnerPlayerIndex(int32 Index) {
	const int32 OwnerPlayerIndex = UMyGameInstance::GetInstance()->GetUserData()->GetPlayerIndex();
	return Index == OwnerPlayerIndex;
}
