/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include <strix/client/ingame/object/NetworkObject.h>

class AActor;
class UStrixReplicatorComponent;

/** NetworkObject implementation for use with Unreal Engine.
 */
class UENetworkObject : public strix::client::ingame::object::NetworkObject
{
public:
	UENetworkObject(int typeId);
	UENetworkObject(int typeId, AActor *actor);

	int GetTypeId() const override;
	bool GetShouldReceiveRemoteDestroyEvent() const override;
	strix::client::ingame::object::InstantiableBy GetInstantiableBy() const override;
	strix::client::ingame::object::ConnectionClosedBehaviour GetConnectionClosedBehaviour() const override;

	/** Sets the actor on this network object, but only if the current one is not valid
	 *  @param	actor	The actor to set
	 */
	void SetActorIfNotValid(AActor* actor);

	/** Sets the actor on this network object to null	*/
	void UnsetActor();

	/** 
	 *  Returns the actor reference of this network object.
	 */
	AActor* GetActor()
	{
		return m_actor;
	}

protected:
	void InitObject() override;
	void DestroyObject() override;
	void OnSyncObject() override;
	void OnOwnershipReceived() override;

private:
	AActor * m_actor;
	int m_typeId;
};
