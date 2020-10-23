/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Sync/UEClassNetworkObjectSpawner.h"

#include <strix/client/ingame/object/NetworkObjectSpawner.h>

#include <map>

class UGameInstance;

/** Helper class for managing the type Ids of the replicators.
 *  Stores most of the information in the config files for easier management (git etc.).
 */
class UETypeRegistry
{
public:
	/** Initialize the type registry for use with the specified game instance.
	 *  This reads the Game.ini config file and creates class spawners from the information inside.
	 *  @param	gameInstance	The game instance to use for the creation of class spawners
	 */
	void Init(UGameInstance *gameInstance);

	/** Stores the provided class spawner in the registry and writes the information about it
	 *  to the config file.
	 *  @param	spawner	Spawner to store
	 *  @returns	Type Id of the stored spawner
	 */
	int AddClassSpawner(std::shared_ptr<UEClassNetworkObjectSpawner> spawner);

	/** Create a class spawner
	 *  @param	typeId	Type Id of this spawner (replication type)
	 *  @param	gameInstance	The game instance to create the spawner with
	 *  @param	path	UClass object path
	 *  @returns	Created spawner
	 */
	UEClassNetworkObjectSpawnerPtr CreateClassSpawner(int typeId, UGameInstance *gameInstance, const FString& path);

	/** Access the stored spawner by Type Id
	 *  @param	typeId	Spawner to store
	 *  @returns	Stored spawner with a matching Type Id or nullptr if not found
	 */
	strix::client::ingame::object::NetworkObjectSpawnerPtr GetSpawnerByTypeId(int typeId);

	/** Try to access the stored spawner by path
	 *  @param	path	Path to use
	 *  @param	result	Type Id of the spawner if found
	 *  @returns	Whether the spawner was found or not
	 */
	bool TryGetTypeIdByClassSpawnerPath(FString path, int& result);

	/** Try to get the Type Id by path or generate it if it does not exist
	 *  @param	path	Path to use
	 *  @returns	Found/generated Type Id
	 */
	static int GetOrStoreTypeIdBySpawnerPathInConfigFile(FString path);

	/** Getter function for registered spawners
	 *  @returns	Spawners contained by this registry, segregated by Type Id
	 */
	const std::map<int, UEClassNetworkObjectSpawnerPtr>& GetRegisteredSpawners()
	{
		return m_registeredSpawners;
	}

	// Config file name
	static const FString DefaultConfigFilename;

	// Old config file name, used for backwards compatibility
	static const FString BackwardsCompatibleConfigFilename;

private:
	/** Writes the spawner information to config (Game.ini) file.
	 *  If running in Unreal Editor context also writes this information
	 *  to the DefaultGame.ini config to help with file management/merging.
	 *  @param	path	Path to store
	 *  @param	currentId	The Type Id of the spawner
	 */
	static void WriteSpawnerInformationToConfigs(const FString& path, int currentId);

	/** Name of the section in the config file - deprecated
	 */
	static const FString OldConfigSectionName;

	/** Name of the section in the config file
	 */
	static const FString ConfigSectionName;

	static const FString MaxStoredIdConfigKey;
	int m_maxStoredId = 0;

	std::map<int, UEClassNetworkObjectSpawnerPtr> m_registeredSpawners;
	TMap<FString, int> m_typeIdByPath;

};