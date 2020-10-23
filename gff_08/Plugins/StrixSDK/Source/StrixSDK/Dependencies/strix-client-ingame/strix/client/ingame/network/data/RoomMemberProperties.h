#pragma once

#include <strix/net/object/WrapperObject.h>
#include <strix/net/object/ObjectAdapter.h>

#include <memory>
#include <string>
#include <utility>

namespace strix { namespace client { namespace ingame { namespace network { namespace data {

/**
 *  Container for a room member's properties. The room member's name is a known 
 *  property field while other properties are customizable
 */
class RoomMemberProperties
{
public:
	RoomMemberProperties()
	{
	}

	RoomMemberProperties(std::string name) : m_name(std::move(name))
	{
	}

	/**
	 *  Get the name of this room member
	 *  @returns	The name
	 */
	const std::string &GetName() const { return m_name; }

	/**
	 *  Set the name of this room member
	 *  @param	name	The name
	 */
	void SetName(std::string name) { m_name = std::move(name); }

	/**
	 *  Set this room member's custom properties, excluding it's name
	 *  @param	properties	The properties to set
	 */
	void SetPropertiesMap(net::object::ObjectMap properties) { m_properties = properties; }

	/**
	 *  Get this room member's custom properties, excluding it's name
	 *  @returns	The properties
	 */
	const net::object::ObjectMap &GetPropertiesMap() const { return m_properties; }

	/**
	 *  Set a property of this room member
	 *  @param	key	The name of the property
	 *  @param	value	The value of the property
	 */
	void SetProperty(std::string key, net::object::ObjectAdapter value)
	{
		m_properties->emplace(std::make_pair(net::object::ObjectAdapter(key), std::move(value)));
	}

	/**
	 *  Get a property of this room member
	 *  @param	key	The name of the property
	 *  @returns	The value of the property, or null if it does not exist
	 */
	net::object::ObjectPtr GetProperty(const std::string &key) const
	{
		const auto it = m_properties->find(net::object::ObjectAdapter(key));
		if (it == m_properties->end())
		{
			return nullptr;
		}

		return it->second;
	}

	/**
	 *  Get a map representation of this room members properties.
	 *  The map contains the key "name" with a StringObject value and 
	 *  a key "properties" with an ObjectMap value
	 *  @returns	The combined map
	 */
	std::map<std::string, strix::net::object::ObjectPtr> ToMap() const
	{
		return {
			{
				{
					"name",
					std::make_shared<net::object::StringObject>(m_name)
				},
				{
					"properties",
					std::make_shared<net::object::ObjectMap>(m_properties)
				},
			}
		};
	}

	/**
	 *  Set the properties of this object by converting a property map.
	 *  The map should contain the key/value types "name": StringObject and 
	 *  "properties": ObjectMap
	 *  @param	objectMap	The object map to convert from
	 */
	void FromObjectMap(const net::object::ObjectMap &objectMap)
	{
		auto it = objectMap->find(std::make_shared<net::object::StringObject>("name"));
		if (it != objectMap->end() && it->second->InstanceOf<net::object::StringObject>())
		{
			m_name = std::static_pointer_cast<net::object::StringObject>(it->second)->Get();
		}

		it = objectMap->find(std::make_shared<net::object::StringObject>("properties"));
		if (it != objectMap->end() && it->second->InstanceOf<net::object::ObjectMap>())
		{
			m_properties = std::static_pointer_cast<net::object::ObjectMap>(it->second)->Get();
		}
	}

private:
	std::string m_name;
	net::object::ObjectMap m_properties;
};

typedef std::shared_ptr<RoomMemberProperties> RoomMemberPropertiesPtr;

} } } } }
