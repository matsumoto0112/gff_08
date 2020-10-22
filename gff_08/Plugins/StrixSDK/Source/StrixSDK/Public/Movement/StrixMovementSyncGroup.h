/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include <strix/client/ingame/sync/ManualSyncGroup.h>

#include <functional>

/**
 *  SyncGroup implementation used by the Strix movement synchronizers.
 *  
 *  The difference between this and the manual sync group is the post apply function
 *  that is being called whenever properties are updated.
 */
class StrixMovementSyncGroup : public strix::client::ingame::sync::ManualSyncGroup
{
public:
	StrixMovementSyncGroup(std::function<void()> postApplyFunction)
		: m_postApplyFunction(std::move(postApplyFunction))
	{
	}

	/** Update the properties from the received map and call the post update callback if successful.
	 *  @param	properties	Map containing the properties to update
	 *  @returns	True if any properties were applied
	 */
	bool ApplyProperties(const strix::client::ingame::sync::PropertyMap& properties) override
	{
		if (strix::client::ingame::sync::ManualSyncGroup::ApplyProperties(properties) && m_postApplyFunction)
		{
			m_postApplyFunction();
			return true;
		}
		return false;
	}

	/** Get the post apply function being used by this sync group
	 *  @returns	The post apply function used by this sync group
	 */
	std::function<void()> GetPostApplyFunction() const
	{
		return m_postApplyFunction;
	}

	/** Set the post apply function being used by this sync group
	 *  @param	postApplyFunction	The function to set
	 */
	void SetPostApplyFunction(std::function<void()> postApplyFunction)
	{
		m_postApplyFunction = postApplyFunction;
	}

	/** Clear the stored post apply function
	 */
	void ClearPostApplyFunction()
	{
		m_postApplyFunction = nullptr;
	}

private:
	std::function<void()> m_postApplyFunction;
};
