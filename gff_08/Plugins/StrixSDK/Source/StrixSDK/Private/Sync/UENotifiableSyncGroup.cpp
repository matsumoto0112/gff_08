/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Sync/UENotifiableSyncGroup.h"

bool UENotifiableSyncGroup::ApplyProperties(const strix::client::ingame::sync::PropertyMap& properties)
{
	const std::map<int, strix::net::object::ObjectPtr> &propMap = properties.GetMap();
	std::set<int> functionsToCall;
	bool didApply = false;
	for (strix::client::ingame::sync::SyncPropertyPtr &prop : m_syncProperties)
	{
		const int propertyId = prop->GetPropertyId();
		strix::net::object::ObjectPtr objectValue;

		bool hasValue = false;
		if (propertyId != 0)
		{
			hasValue = properties.TryGet(propertyId, objectValue);
		}
		else
		{
			hasValue = properties.TryGet(prop->GetPropertyName(), objectValue);
		}

		if (hasValue)
		{
			didApply = true;
			prop->SetObjectValue(objectValue);
			if (m_notifyFunctions.find(prop->GetPropertyId()) != m_notifyFunctions.end())
			{
				functionsToCall.insert(prop->GetPropertyId());
			}
		}
	}
	for (auto& propertyId : functionsToCall)
	{
	    auto it = m_notifyFunctions.find(propertyId);
	    if (it != m_notifyFunctions.end() && it->second.second->IsValidLowLevel())
	    {
		 if (UFunction* func = it->second.second->FindFunction(FName(*it->second.first)))
		 {
		     it->second.second->ProcessEvent(func, nullptr);
		 }
	    }
	}
	return didApply;
}

void UENotifiableSyncGroup::AddNotifyFunction(UFunction* func, UObject* object, strix::client::ingame::sync::SyncPropertyPtr sync)
{
    m_notifyFunctions[sync->GetPropertyId()] = std::make_pair(func->GetName(), object);
}
