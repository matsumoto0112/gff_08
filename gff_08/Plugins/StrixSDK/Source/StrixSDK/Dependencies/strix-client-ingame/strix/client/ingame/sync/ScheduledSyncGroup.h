#pragma once

#include <strix/client/ingame/sync/SyncGroup.h>

#include <chrono>

namespace strix { namespace client { namespace ingame { namespace sync {

/**
 *  Controller for a group of properties. Handles adding, removing, and updating properties
 *  
 *  Accepts updates anytime, but only propagates changes a number of times a second
 */
class ScheduledSyncGroup : public SyncGroup
{
public:
	ScheduledSyncGroup();

	/**
	 *  Construct a ScheduledSyncGroup with the given update interval
	 *  @param	interval	The interval between updates in milliseconds
	 */
	ScheduledSyncGroup(const std::chrono::milliseconds interval);

	/**
	 *  Get if remote changes to these properties should be updated here. Always returns true for this group type
	 *  @returns	True if the changes should update
	 */
	bool ShouldReceiveChanges() const override;

	/**
	 *  Get whether this group should propagate its local changes.
	 *  @returns	True if the time between the last CollectProperties call and now is greater than the interval
	 */
	bool ShouldPropagateChanges() const override;

	/**
	 *  Get the local values of all the properties and store them in the map
	 *  @param	outputProperties	The output map
	 */
	void CollectProperties(PropertyMap& outputProperties) override;

	/**
	 *  Set the update rate of the group
	 *  @param	ticksPerSecond	The number of updates a second
	 */
	void SetTicksPerSecond(int ticksPerSecond);

	/**
	 *  Get the tick rate
	 *  @returns	The ticks per second
	 */
	int GetTicksPerSecond() const;

	/**
	 *  Set the interval between updates
	 *  @param	interval	Time in milliseconds
	 */
	void SetTickInterval(std::chrono::milliseconds interval);

	/**
	 *  Get the interval between updates
	 *  @returns	The interval in milliseconds
	 */
	std::chrono::milliseconds GetTickInterval() const;

protected:
	std::chrono::milliseconds m_interval;
	std::chrono::steady_clock::time_point m_lastTick;
};

} } } }
