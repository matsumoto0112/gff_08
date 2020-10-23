#pragma once

#include <memory>
#include <string>

namespace strix { namespace net { namespace object {
class Object;
typedef std::shared_ptr<Object> ObjectPtr;
} } }

namespace strix { namespace client { namespace ingame { namespace sync {

class PropertyMap;
typedef std::shared_ptr<PropertyMap> ReplicatorPropertiesPtr;

// Todo: Consider permissions here (e.g. LocalWriteOnly, RoomOwnerWriteOnly)
/**
 *  Interface for synchronizable properties
 */
class SyncProperty
{
public:
	virtual ~SyncProperty() = default;

	/**
	 *  Get this property's ID
	 *  @returns	The ID
	 */
	virtual int GetPropertyId() const { return 0; }

	/**
	 *  Get this property's name
	 *  @returns	The name of the property
	 */
	virtual const std::string &GetPropertyName() const = 0;

	/**
	 *  Get the value of this property converted to a strix Object
	 *  @returns	The object value
	 */
	virtual net::object::ObjectPtr GetObjectValue() = 0;

	/**
	 *  Set the value of this property converted from a strix Object
	 *  @param	objectValue	The object value
	 */
	virtual void SetObjectValue(net::object::ObjectPtr objectValue) = 0;
};

typedef std::shared_ptr<SyncProperty> SyncPropertyPtr;

} } } }
