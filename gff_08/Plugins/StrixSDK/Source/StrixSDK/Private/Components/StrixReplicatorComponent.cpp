/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Components/StrixReplicatorComponent.h"

#include "StrixNetworkFacade.h"
#include "UELogHandler.h"
#include "GameFramework/Actor.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Sync/UENetworkObject.h"
#include "Sync/UENotifiableSyncGroup.h"
#include "Sync/UESyncProperties.h"
#include "Sync/UETypeRegistry.h"
#include "Util/ActorUtil.h"

#include <strix/client/ingame/network/RoomContext.h>
#include <strix/client/ingame/object/NetworkObjectManager.h>

using namespace strix::client::core::util;
using namespace strix::client::ingame::sync;

const FName UStrixReplicatorComponent::StrixRemoteObjectActorTag = FName("StrixRemoteObject");

// Sets default values for this component's properties
UStrixReplicatorComponent::UStrixReplicatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	TicksPerSecond = 5;
	InstantiableBy = EInstantiableBy::Anyone;
	ConnectionClosedBehaviour = EConnectionClosedBehaviour::Delete;
	ShouldReceiveDestroyEvents = true;
	AutoRegisterProperties = true;
	TypeId = -1;
	ChannelId = 0;
	IsOwner = true;
	IsOwnerAndReplicating = false;
	IsReplicating = false;

	m_roomContextOpenDelegateHandle = 0;
	m_defaultSyncGroup = std::make_shared<UENotifiableSyncGroup>();
}

strix::client::ingame::object::NetworkObjectPtr UStrixReplicatorComponent::GetNetworkObject() const
{
	return m_networkObject;
}

void UStrixReplicatorComponent::BeginPlay()
{
	Super::BeginPlay();

	AddReplicatedBlueprintProperties();
	
	m_defaultSyncGroup->SetTicksPerSecond(TicksPerSecond);

	if (GetOwner()->ActorHasTag(StrixRemoteObjectActorTag))
	{
		return;
	}
	
	// Todo: Generate TypeId if == -1?
	auto strixNetwork = UStrixNetworkFacade::GetInstance(this);
	if (IsValid(strixNetwork))
	{
		const auto roomContextOpenCallback = MethodBinding::BindRaw(this, &UStrixReplicatorComponent::OnRoomContextOpen);
		m_roomContextOpenDelegateHandle = strixNetwork->AddRoomContextOpenHandler(roomContextOpenCallback);
		if (auto roomContext = strixNetwork->GetRoomContextByChannelId(ChannelId))
		{
			OnRoomContextOpen(ChannelId, std::move(roomContext));
		}
	}
	else
	{
		UE_LOG(LogStrix, Error, TEXT("StrixNetwork isn't initialized"));
	}
}

// ToDo: check performance and make tests for every scenario
void UStrixReplicatorComponent::OnRegister()
{
	Super::OnRegister();

#ifndef WITH_EDITOR
	if (TypeId != -1)
		return;
#endif

	// only check/store type id for blueprint objects
	auto strixNetwork = UStrixNetworkFacade::GetInstance(this);
	if (IsValid(strixNetwork))
	{
		std::shared_ptr<UETypeRegistry> typeRegistry = strixNetwork->GetTypeRegistry();

		if (typeRegistry)
		{
			int typeId = -1;

			if (!IsStaticWorldObject())
			{
				if (typeRegistry->TryGetTypeIdByClassSpawnerPath(GetOwner()->GetClass()->GetPathName(), typeId))
				{
					TypeId = typeId;
					return;
				}

#if WITH_EDITOR
				TypeId = typeRegistry->AddClassSpawner(BuildClassNetworkObjectSpawner());
#else
				TypeId = -1;
#endif
			}
#ifndef WITH_EDITOR
			else
			{
				UE_LOG(LogStrix, Log, TEXT("UStrixReplicatorComponent::OnRegister - Replicating static world objects is currently not supported."));
			}
#endif
		}
	}
#if WITH_EDITOR
	else
	{
		UObject* archetype = GetArchetype();
		UStrixReplicatorComponent* castedArchetype = (archetype) ? Cast<UStrixReplicatorComponent>(archetype) : nullptr;
		if (!IsStaticWorldObject())
		{
			TypeId = UETypeRegistry::GetOrStoreTypeIdBySpawnerPathInConfigFile(GetOwner()->GetClass()->GetPathName());
			if (castedArchetype && castedArchetype->TypeId == -1)
			{
				castedArchetype->TypeId = TypeId;
			}
		}
		else
		{
			if (castedArchetype)
			{
				if (castedArchetype->TypeId != -1)
				{
					TypeId = castedArchetype->TypeId;
					return;
				}
			}
			UE_LOG(LogStrix, Log, TEXT("UStrixReplicatorComponent::OnRegister - Replicating static world objects is currently not supported."));
		}
	}
#endif

}

void UStrixReplicatorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	auto strixNetwork = UStrixNetworkFacade::GetInstance(this);
	if (IsValid(strixNetwork))
	{
		strixNetwork->RemoveRoomContextOpenHandler(m_roomContextOpenDelegateHandle);

		if (m_networkObject)
		{
			strixNetwork->DeregisterRpcProcedures(ChannelId, m_networkObject->GetNetworkInstanceId());
		}
	}

	if (m_networkObject)
	{
		m_networkObject->UnsetActor();
		m_networkObject->DestroyNetworkInstance((!m_networkObject->IsOwner() && EndPlayReason == EEndPlayReason::Destroyed));
	}
}

int UStrixReplicatorComponent::GetTicksPerSecond() const
{
	return TicksPerSecond;
}

void UStrixReplicatorComponent::SetTicksPerSecond(int newTicksPerSecond)
{
	TicksPerSecond = newTicksPerSecond;
	m_defaultSyncGroup->SetTicksPerSecond(newTicksPerSecond);
}

bool UStrixReplicatorComponent::GetIsOwner() const
{
	if (m_networkObject)
	{
		return m_networkObject->IsOwner();
	}

	return !GetOwner()->ActorHasTag(StrixRemoteObjectActorTag);
}

bool UStrixReplicatorComponent::GetIsReplicating() const
{
	return m_networkObject && m_networkObject->IsReplicating();
}

bool UStrixReplicatorComponent::GetIsOwnerAndReplicating() const
{
	return m_networkObject && m_networkObject->IsOwnerAndReplicating();
}

void UStrixReplicatorComponent::AddSyncProperty(strix::client::ingame::sync::SyncPropertyPtr syncProperty)
{
	m_defaultSyncGroup->AddProperty(syncProperty);
}

void UStrixReplicatorComponent::AddSyncGroup(strix::client::ingame::sync::SyncGroupPtr syncGroup)
{
	if (m_networkObject)
	{
		m_networkObject->AddSyncGroup(syncGroup);
	}
	else
	{
		m_syncGroups.push_back(syncGroup);
	}
}

void UStrixReplicatorComponent::RemoveSyncGroup(strix::client::ingame::sync::SyncGroupPtr syncGroup)
{
	if (m_networkObject)
	{
		m_networkObject->RemoveSyncGroup(syncGroup);
	}
	else
	{
		auto it = std::find(m_syncGroups.begin(), m_syncGroups.end(), syncGroup);
		if (it != m_syncGroups.end())
		{
			m_syncGroups.erase(it);
		}
	}
}

strix::client::ingame::sync::SyncGroupPtr UStrixReplicatorComponent::GetDefaultSyncGroup()
{
	return m_defaultSyncGroup;
}

void UStrixReplicatorComponent::OnRoomContextOpen(int roomContextChannelId, strix::client::ingame::network::RoomContextPtr roomContext)
{
	if (!m_networkObject && roomContextChannelId == ChannelId)
	{
		strix::client::ingame::object::NetworkObjectManagerPtr networkObjectManager = roomContext->GetNetworkObjectManager();
		strix::client::ingame::object::NetworkObjectSpawnerPtr spawner = networkObjectManager->FindSpawner(TypeId);
		if (!spawner)
		{
			UE_LOG(LogStrix, Verbose, TEXT("UStrixReplicatorComponent::OnRoomContextOpen - NetworkObjectSpawner %d doesn't exist."), TypeId);
			return;
		}

		AActor * ownerActor = GetOwner();
		if (networkObjectManager->CanInstantiate(static_cast<strix::client::ingame::object::InstantiableBy>(InstantiableBy)))
		{
			m_networkObject = std::make_shared<UENetworkObject>(TypeId, ownerActor);
			RegisterPreparedSyncGroups();
			networkObjectManager->AddLocalInstance(m_networkObject);
		}
		else
		{
			ownerActor->Destroy();
		}
	}
}

void UStrixReplicatorComponent::InitializeRemoteInstance()
{
	m_networkObject = std::make_shared<UENetworkObject>(TypeId, GetOwner());
	RegisterPreparedSyncGroups();
}

void UStrixReplicatorComponent::InitializeRemoteInstance(UENetworkObjectPtr networkObject)
{
	m_networkObject = networkObject;
	RegisterPreparedSyncGroups();
}

void UStrixReplicatorComponent::RegisterPreparedSyncGroups()
{
	if (m_networkObject)
	{
		m_networkObject->AddSyncGroup(m_defaultSyncGroup);
		for (const auto &syncGroup : m_syncGroups)
		{
			m_networkObject->AddSyncGroup(syncGroup);
		}
		m_syncGroups.clear();
	}
}

void UStrixReplicatorComponent::AddReplicatedBlueprintProperties()
{
	if (!AutoRegisterProperties)
	{
		return;
	}

	ActorUtil::IteratePropertyTree(
		GetOwner(), false, [&](UObject *object, UProperty *prop)
	{
		if (Cast<UBlueprintGeneratedClass>(object->GetClass()) && prop->HasAnyPropertyFlags(CPF_Net))
		{
			if (prop->HasAnyPropertyFlags(CPF_RepNotify))
			{
				UESyncPropertyUtils::SyncUEProperty(prop, object, m_defaultSyncGroup, prop->RepNotifyFunc, GetOwner());
			}
			else
			{
				UESyncPropertyUtils::SyncUEProperty(prop, object, m_defaultSyncGroup);
			}
		}
	}
	);
}

bool UStrixReplicatorComponent::IsStaticWorldObject()
{
	// ToDo: test this for every situation
#if WITH_EDITOR
	return !(GetOwner()->HasAllFlags(RF_Transient));
#else
	return GetOwner()->HasAllFlags(RF_WasLoaded);
#endif
}

std::shared_ptr<UEClassNetworkObjectSpawner> UStrixReplicatorComponent::BuildClassNetworkObjectSpawner()
{
	return std::make_shared<UEClassNetworkObjectSpawner>(GetOwner()->GetGameInstance(), GetOwner()->GetClass());
}
