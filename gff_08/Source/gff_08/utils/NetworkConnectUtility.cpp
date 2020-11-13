// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkConnectUtility.h"

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