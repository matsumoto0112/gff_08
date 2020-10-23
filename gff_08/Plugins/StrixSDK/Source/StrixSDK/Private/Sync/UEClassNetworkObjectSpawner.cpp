/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Sync/UEClassNetworkObjectSpawner.h"

#include "UELogHandler.h"
#include "Components/StrixReplicatorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "Sync/UENetworkObject.h"
#include "Util/ActorUtil.h"
#include "UObject/Class.h"

UEClassNetworkObjectSpawner::UEClassNetworkObjectSpawner(UGameInstance* gameInstance, UClass* actorClass)
	: m_typeId(-1), m_gameInstance(gameInstance), m_actorClass(actorClass->GetAuthoritativeClass())
{
}

UEClassNetworkObjectSpawner::UEClassNetworkObjectSpawner(int typeId, UGameInstance *gameInstance, UClass* actorClass)
	: m_typeId(typeId), m_gameInstance(gameInstance), m_actorClass(actorClass->GetAuthoritativeClass())
{
}

strix::client::ingame::object::NetworkObjectPtr UEClassNetworkObjectSpawner::CreateInstance()
{
	AActor* actor = SpawnUnrealActor();

	if (!actor)
	{
		return nullptr;
	}

	if (auto replicator = actor->FindComponentByClass<UStrixReplicatorComponent>())
	{
		replicator->InitializeRemoteInstance();
		return replicator->GetNetworkObject();
	}

	UE_LOG(LogStrix, Error, TEXT("Tried to instantiate an object without a StrixReplicatorComponent"));
	return nullptr;
}

strix::client::ingame::object::NetworkObjectPtr UEClassNetworkObjectSpawner::CreatePausedInstance()
{
	return std::make_shared<UENetworkObject>(m_typeId);
}

void UEClassNetworkObjectSpawner::UnpauseInstance(strix::client::ingame::object::NetworkObjectPtr networkObject)
{
	AActor* actor = SpawnUnrealActor();

	if (!actor)
	{
		return;
	}

	std::shared_ptr<UENetworkObject> ueNetworkObject = std::static_pointer_cast<UENetworkObject>(networkObject);
	ueNetworkObject->SetActorIfNotValid(actor);

	if (auto replicator = actor->FindComponentByClass<UStrixReplicatorComponent>())
	{
		replicator->InitializeRemoteInstance(ueNetworkObject);
		ueNetworkObject->Unpause();
	}
	else
	{
		UE_LOG(LogStrix, Error, TEXT("Tried to instantiate an object without a StrixReplicatorComponent"));
	}
}

UClass* UEClassNetworkObjectSpawner::GetActorClass()
{
	return m_actorClass;
}

AActor* UEClassNetworkObjectSpawner::SpawnUnrealActor()
{
	UWorld *world = m_gameInstance->GetWorld();
	if (!world)
	{
		UE_LOG(LogStrix, Error, TEXT("Tried to instantiate an object without an active UWorld"));
		return nullptr;
	}
	
	const FTransform transform;

	AActor *actor = world->SpawnActorDeferred<AActor>(
		m_actorClass, transform,
		nullptr, nullptr, 
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	actor->Tags.Add(UStrixReplicatorComponent::StrixRemoteObjectActorTag);
	
	// Todo: Make this optional?
	ActorUtil::DisablePawnControl(actor);

	// Disable actor until OnSync
	ActorUtil::DisableActor(actor);
	actor->FinishSpawning(transform);

#if WITH_EDITOR
	FString className = m_actorClass->GetName();
	className.Append(" (Remote)");
	actor->SetActorLabel(className, true);
#endif

	return actor;
}
