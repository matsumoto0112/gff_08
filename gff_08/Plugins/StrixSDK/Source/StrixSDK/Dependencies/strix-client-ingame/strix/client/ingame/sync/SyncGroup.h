#pragma once

#include <memory>
#include <vector>

namespace strix { namespace client { namespace ingame { namespace sync {

class PropertyMap;
class SyncProperty;

typedef std::shared_ptr<SyncProperty> SyncPropertyPtr;

/**
 *  Controller for a group of properties. Handles adding, removing, and updating properties
 */
class SyncGroup
{
public:
	virtual ~SyncGroup();

	/**
	 *  Add the property to the sync group
	 *  @param	syncProperty	The property to add
	 */
	void AddProperty(SyncPropertyPtr syncProperty);

	/**
	 *  Remove the property from the sync group
	 *  @param	syncProperty	The property to remove
	 */
	void RemoveProperty(SyncPropertyPtr syncProperty);

	/**
	 *  Get if the local changes to these properties should be sent to other clients
	 *  @returns	True if should propagate
	 */
	virtual bool ShouldPropagateChanges() const = 0;

	/**
	 *  Get if remote changes to these properties should be updated locally
	 *  @returns	True if the changes should update
	 */
	virtual bool ShouldReceiveChanges() const = 0;

	/**
	 *  Get the current values of all the properties and store them in the map
	 *  @param	outputProperties	The output map
	 */
	virtual void CollectProperties(PropertyMap &outputProperties);

	/**
	 *  Set the current values of all the properties to the values in the given map
	 *  @param	properties	The new values
	 */
	virtual bool ApplyProperties(const PropertyMap &properties);

protected:
	std::vector<SyncPropertyPtr> m_syncProperties;
};

typedef std::shared_ptr<SyncGroup> SyncGroupPtr;

} } } }
