/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include <strix/client/ingame/object/NetworkObjectSpawner.h>

class AActor;
class FString;
class UClass;
class UGameInstance;
class UWorld;

/** NetworkObjectSpawner implementation for use with Unreal Engine.
 *  Spawns actors based on the UClass.
 */
class UEClassNetworkObjectSpawner : public strix::client::ingame::object::NetworkObjectSpawner
{
public:
	UEClassNetworkObjectSpawner(UGameInstance *gameInstance, UClass* actorClass);

	UEClassNetworkObjectSpawner(int typeId, UGameInstance *gameInstance, UClass* actorClass);

	strix::client::ingame::object::NetworkObjectPtr CreateInstance() override;

	strix::client::ingame::object::NetworkObjectPtr CreatePausedInstance() override;

	void UnpauseInstance(strix::client::ingame::object::NetworkObjectPtr networkObject) override;

	/** Getter for the UClass used by this spawner
	 *  @returns UClass used by this spawner
	 */
	UClass* GetActorClass();

	/** Setter for the type Id of this spawner
	 *  @param	typeId	The type Id to set
	 */
	void SetTypeId(int typeId)
	{
		m_typeId = typeId;
	}
	
private:
	/** Spawn an actor using this spawner
	 *  @returns The spawned actor
	 */
	AActor* SpawnUnrealActor();

	int m_typeId;
	UGameInstance *m_gameInstance;
	UClass *m_actorClass;
};

typedef std::shared_ptr<UEClassNetworkObjectSpawner> UEClassNetworkObjectSpawnerPtr;
