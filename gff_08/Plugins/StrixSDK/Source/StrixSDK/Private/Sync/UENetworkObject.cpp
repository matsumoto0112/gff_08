/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Sync/UENetworkObject.h"

#include "Components/StrixReplicatorComponent.h"
#include "Components/StrixMovementSynchronizer.h"
#include "GameFramework/Actor.h"
#include "Util/ActorUtil.h"

UENetworkObject::UENetworkObject(int typeId)
	: NetworkObject(), m_actor(nullptr), m_typeId(typeId)
{
}

UENetworkObject::UENetworkObject(int typeId, AActor *actor)
	: NetworkObject(), m_actor(actor), m_typeId(typeId)
{
}

int UENetworkObject::GetTypeId() const
{
	if (IsValid(m_actor))
	{
		if (const auto replicator = m_actor->FindComponentByClass<UStrixReplicatorComponent>())
		{
			return replicator->TypeId;
		}
	}
	return m_typeId;
}

bool UENetworkObject::GetShouldReceiveRemoteDestroyEvent() const
{
	if (IsValid(m_actor))
	{
		if (const auto replicator = m_actor->FindComponentByClass<UStrixReplicatorComponent>())
		{
			return replicator->ShouldReceiveDestroyEvents;
		}
	}
	return true;
}

strix::client::ingame::object::InstantiableBy UENetworkObject::GetInstantiableBy() const
{
	if (IsValid(m_actor))
	{
		if (const auto replicator = m_actor->FindComponentByClass<UStrixReplicatorComponent>())
		{
			return static_cast<strix::client::ingame::object::InstantiableBy>(replicator->InstantiableBy);
		}
	}
	return strix::client::ingame::object::InstantiableBy::Anyone;
}

strix::client::ingame::object::ConnectionClosedBehaviour UENetworkObject::GetConnectionClosedBehaviour() const
{
	if (IsValid(m_actor))
	{
		if (const auto replicator = m_actor->FindComponentByClass<UStrixReplicatorComponent>())
		{
			return static_cast<strix::client::ingame::object::ConnectionClosedBehaviour>(replicator->ConnectionClosedBehaviour);
		}
	}
	return strix::client::ingame::object::ConnectionClosedBehaviour::Delete;
}

void UENetworkObject::SetActorIfNotValid(AActor* actor)
{
	if (!IsValid(m_actor))
	{
		m_actor = actor;
	}
}

void UENetworkObject::UnsetActor()
{
	m_actor = nullptr;
}

void UENetworkObject::InitObject()
{
	if (const auto replicator = m_actor->FindComponentByClass<UStrixReplicatorComponent>())
	{
		replicator->OnInit.Broadcast();
	}
}

void UENetworkObject::DestroyObject()
{
	if (m_actor)
	{
		auto replicator = m_actor->FindComponentByClass<UStrixReplicatorComponent>();

		if (replicator)
		{
			replicator->OnDestroy.Broadcast();
		}

		if (!m_actor->IsActorBeingDestroyed())
		{
			m_actor->Destroy();
		}
	}
	else
	{
		DestroyNetworkInstance(true);
	}
}

void UENetworkObject::OnSyncObject()
{
	if (IsValid(m_actor))
	{
		if (auto replicator = m_actor->FindComponentByClass<UStrixReplicatorComponent>())
		{
			replicator->OnSyncBegin.Broadcast();
			auto actor = replicator->GetOwner();
			if (actor->ActorHasTag(UStrixReplicatorComponent::StrixRemoteObjectActorTag))
			{
				ActorUtil::EnableActor(actor);
			}
		}
	}
}

void UENetworkObject::OnOwnershipReceived()
{
	if (IsValid(m_actor))
	{
		if (auto replicator = m_actor->FindComponentByClass<UStrixReplicatorComponent>())
		{	
			replicator->OnOwnershipReceived.Broadcast();
			if(auto movementComponent = m_actor->FindComponentByClass<UStrixMovementSynchronizer>())
			{
				movementComponent->ResetSynchronizer();
			}
		}
	}
}
