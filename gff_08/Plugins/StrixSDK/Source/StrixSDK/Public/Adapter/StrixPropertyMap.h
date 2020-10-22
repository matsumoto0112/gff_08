/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once
#include "CoreMinimal.h"
#include <strix/net/object/ObjectAdapter.h>
#include <strix/net/object/WrapperObject.h>
#include "StrixPropertyMap.generated.h"

/** Wrapper class for the internal string-object property map, used by Strix libraries.
 *  Used extensively in Customizable... models.
 */
USTRUCT(BlueprintType)
struct FStrixPropertyMap
{
	GENERATED_BODY()

	FStrixPropertyMap() {}
	FStrixPropertyMap(const std::map<std::string, strix::net::object::ObjectPtr>& propertyMap) : m_propertyMap(propertyMap) {}

	/** Convert the wrapped map to one used by Strix functions. 
	 *  This divides the properties into known and unknown ones.
	 *  The known ones are stored directly in the result map.
	 *  The unknown ones are packed into internal "properties" map that is stored in the result map afterwards.
	 *  @param	strixPropertyMap	The property map to convert
	 *  @param	knownNetworkFieldNames	The set containing the names of the known fields
	 *  @returns	The converted map
	 */
	static std::map<std::string, strix::net::object::ObjectPtr> CreateNetworkPropertyMap(const FStrixPropertyMap& strixPropertyMap, const std::set<std::string> knownNetworkFieldNames)
	{
		std::map<std::string, strix::net::object::ObjectPtr> result;
		std::shared_ptr<strix::net::object::ObjectMap> customizableProperties = std::make_shared<strix::net::object::ObjectMap>();

		for (auto entry : strixPropertyMap.m_propertyMap)
		{
			auto setIt = knownNetworkFieldNames.find(entry.first);
			if (setIt != knownNetworkFieldNames.end())
			{
				result.emplace(std::make_pair(entry.first, entry.second));
			}
			else
			{
				customizableProperties->Get().emplace(std::make_pair(strix::net::object::ObjectAdapter(entry.first), entry.second));
			}
		}

		result.emplace(std::make_pair("properties", customizableProperties));

		return result;
	}

	std::map<std::string, strix::net::object::ObjectPtr> m_propertyMap;
};