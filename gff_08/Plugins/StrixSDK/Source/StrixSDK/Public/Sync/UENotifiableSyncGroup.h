/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"

#include <strix/client/ingame/sync/SyncProperty.h>
#include <strix/client/ingame/sync/SyncGroup.h>
#include <strix/client/ingame/sync/PropertyMap.h>

#include "strix/client/ingame/sync/ScheduledSyncGroup.h"
#include <unordered_map>

/**
 *  SyncGroup implementation used by the Strix movement synchronizers.
 *  
 *  The difference between this and the scheduled sync group is the collection of notify functions.
 *  If the property has a registered notify function, whenever that property is being updated
 *  the corresponding function is called.
 */
class UENotifiableSyncGroup : public strix::client::ingame::sync::ScheduledSyncGroup
{
public:
	bool ApplyProperties(const strix::client::ingame::sync::PropertyMap& properties) override;

	/** Assigns a notify function to the specified property
	 *  @param	func	UFunction to call
	 *  @param	object	Object to use to call the function
	 *  @param	sync	Sync property to assign the function to
	 */
	void AddNotifyFunction(UFunction* func, UObject* object, strix::client::ingame::sync::SyncPropertyPtr sync);

private:

	std::unordered_map<int, std::pair<FString, UObject*>> m_notifyFunctions;
};

typedef std::shared_ptr<UENotifiableSyncGroup> UENotifiableSyncGroupPtr;
