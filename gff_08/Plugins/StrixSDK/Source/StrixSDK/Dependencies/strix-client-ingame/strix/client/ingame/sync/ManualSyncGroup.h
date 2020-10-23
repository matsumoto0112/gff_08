#pragma once

#include <strix/client/ingame/sync/SyncGroup.h>

namespace strix { namespace client { namespace ingame { namespace sync {

/**
 *  Controller for a group of properties. Handles adding, removing, and updating properties
 *  
 *  This group is manually synced
 */
class ManualSyncGroup : public SyncGroup
{
public:
	ManualSyncGroup();

	/**
	 *  Get if remote changes to these properties should be updated locally
	 *  @returns	True if the changes should update
	 */
	bool ShouldReceiveChanges() const override;

	/**
	 *  Get if the local changes to these properties should be sent to other clients
	 *  @returns	True if should propagate
	 */
	bool ShouldPropagateChanges() const override;

	/**
	 *  Get the current values of all the properties and store them in the map
	 *  @param	outputProperties	The output map
	 */
	void CollectProperties(PropertyMap& outputProperties) override;

	/**
	 *  Get if the local changes to these properties should be sent to other clients
	 *  @returns	True if should propagate
	 */
	bool GetShouldPropagate()
	{
		return m_shouldPropagate;
	}

	/**
	 *  Set if the local changes to these properties should be sent to other clients
	 *  @param	shouldPropagate	True if should propagate
	 */
	void SetShouldPropagate(bool shouldPropagate)
	{
		m_shouldPropagate = shouldPropagate;
	}

protected:
	bool m_shouldPropagate;
};

} } } }
