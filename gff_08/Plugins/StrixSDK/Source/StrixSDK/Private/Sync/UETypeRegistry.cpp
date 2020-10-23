/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Sync/UETypeRegistry.h"

#include "CoreUObject.h"
#include "UELogHandler.h"

const FString UETypeRegistry::ConfigSectionName = "Strix.Replicator.GameTypes";
const FString UETypeRegistry::OldConfigSectionName = "Strix.Replicator.Types";
const FString UETypeRegistry::DefaultConfigFilename = "DefaultGameStrixTypes.ini";
const FString UETypeRegistry::BackwardsCompatibleConfigFilename = "DefaultGame.ini";
const FString UETypeRegistry::MaxStoredIdConfigKey = "MaxStoredId";

void UETypeRegistry::Init(UGameInstance *gameInstance)
{
	FString projectConfig = FPaths::Combine(FPaths::ProjectConfigDir(), DefaultConfigFilename);
	FString oldProjectConfig = FPaths::Combine(FPaths::ProjectConfigDir(), BackwardsCompatibleConfigFilename);

	int maxStoredId = 0;
	int oldMaxStoredId = 0;
	int newMaxStoredId = 0;

	GConfig->GetInt(*(OldConfigSectionName), *(MaxStoredIdConfigKey), oldMaxStoredId, oldProjectConfig);
	GConfig->GetInt(*(ConfigSectionName), *(MaxStoredIdConfigKey), newMaxStoredId, projectConfig);

	maxStoredId = oldMaxStoredId + newMaxStoredId;
	m_maxStoredId = maxStoredId;

	if (oldMaxStoredId != 0)
	{
		UE_LOG(LogStrix, Warning, TEXT("UETypeRegistry::Init - This project uses an older version of the Type ID configuration system"))
	}

	// Loop over old type ID values (deprecated)
	for (int i = 1; i <= oldMaxStoredId; ++i)
	{
		FString configLine;
		if (GConfig->GetString(*(OldConfigSectionName), *(FString::FromInt(i)), configLine, oldProjectConfig))
		{
			UEClassNetworkObjectSpawnerPtr spawner = CreateClassSpawner(i, gameInstance, configLine);

			if (spawner)
			{
				m_registeredSpawners.insert(std::make_pair(i, spawner));

				if (m_typeIdByPath.Contains(configLine))
				{
					UE_LOG(LogStrix, Warning, TEXT("UETypeRegistry::Init - Duplicate type paths. Replication will not work properly, check the config files!"));
					continue;
				}
				m_typeIdByPath.Add(configLine, i);
			}
		}
	}

	for (int i = 1; i <= newMaxStoredId; ++i)
	{
		FString configLine;
		if (GConfig->GetString(*(ConfigSectionName), *(FString::FromInt(i)), configLine, projectConfig))
		{
			UEClassNetworkObjectSpawnerPtr spawner = CreateClassSpawner(i, gameInstance, configLine);

			if (spawner)
			{
				m_registeredSpawners.insert(std::make_pair(i, spawner));

				if (m_typeIdByPath.Contains(configLine))
				{
					UE_LOG(LogStrix, Warning, TEXT("UETypeRegistry::Init - Duplicate type paths. Replication will not work properly, check the config files!"));
					continue;
				}
				m_typeIdByPath.Add(configLine, i);
			}
		}
	}
}

int UETypeRegistry::AddClassSpawner(std::shared_ptr<UEClassNetworkObjectSpawner> spawner)
{
	if (spawner)
	{
		FString path = spawner->GetActorClass()->GetPathName();

		int typeId = ++m_maxStoredId;
		WriteSpawnerInformationToConfigs(path, typeId);
		spawner->SetTypeId(typeId);

		m_registeredSpawners.insert(std::make_pair(typeId, spawner));
		m_typeIdByPath.Add(path, typeId);
		return typeId;
	}
	return -1;
}

UEClassNetworkObjectSpawnerPtr UETypeRegistry::CreateClassSpawner(int typeId, UGameInstance *gameInstance, const FString& path)
{
	UClass* loadedClass = LoadObject<UClass>(nullptr, *path);

	if (loadedClass && IsValid(loadedClass))
		return std::make_shared<UEClassNetworkObjectSpawner>(typeId, gameInstance, loadedClass);
	else
		return nullptr;
}

strix::client::ingame::object::NetworkObjectSpawnerPtr UETypeRegistry::GetSpawnerByTypeId(int typeId)
{
	auto spawnerIt = m_registeredSpawners.find(typeId);

	if (spawnerIt != m_registeredSpawners.end())
	{
		return spawnerIt->second;
	}
	return nullptr;
}

bool UETypeRegistry::TryGetTypeIdByClassSpawnerPath(FString path, int& result)
{
	FString mapKey = path;
	if (m_typeIdByPath.Contains(mapKey))
	{
		result = m_typeIdByPath[mapKey];
		return true;
	}
	return false;
}

int UETypeRegistry::GetOrStoreTypeIdBySpawnerPathInConfigFile(FString path)
{
	FString projectConfig = FPaths::Combine(FPaths::ProjectConfigDir(), DefaultConfigFilename);

	int maxStoredId = 0;
	if (GConfig->GetInt(*(ConfigSectionName), *(MaxStoredIdConfigKey), maxStoredId, projectConfig))
	{
		for (int i = 1; i <= maxStoredId; ++i)
		{
			FString configLine;
			if (GConfig->GetString(*(ConfigSectionName), *(FString::FromInt(i)), configLine, projectConfig))
			{
				if (configLine.Equals(path))
				{
					return i;
				}
			}
		}
	}

	// Check old config for backwards compatibility (deprecated)
	FString oldProjectConfig = FPaths::Combine(FPaths::ProjectConfigDir(), BackwardsCompatibleConfigFilename);
	maxStoredId = 0;
	if (GConfig->GetInt(*(OldConfigSectionName), *(MaxStoredIdConfigKey), maxStoredId, oldProjectConfig))
	{
		for (int i = 1; i <= maxStoredId; ++i)
		{
			FString configLine;
			if (GConfig->GetString(*(OldConfigSectionName), *(FString::FromInt(i)), configLine, oldProjectConfig))
			{
				if (configLine.Equals(path))
				{
					return i;
				}
			}
		}
	}

	WriteSpawnerInformationToConfigs(path, ++maxStoredId);
	return maxStoredId;
}

void UETypeRegistry::WriteSpawnerInformationToConfigs(const FString& path, int currentId)
{
	FString projectConfig = FPaths::Combine(FPaths::ProjectConfigDir(), DefaultConfigFilename);

	GConfig->SetInt(*(ConfigSectionName), *(MaxStoredIdConfigKey), currentId, projectConfig);
	GConfig->SetString(*(ConfigSectionName), *(FString::FromInt(currentId)), *(path), projectConfig);
	GConfig->Flush(false, projectConfig);
}
