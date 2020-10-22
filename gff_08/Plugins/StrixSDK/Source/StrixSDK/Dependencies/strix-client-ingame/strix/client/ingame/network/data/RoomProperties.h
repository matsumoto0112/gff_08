#pragma once

#include <strix/net/object/WrapperObject.h>
#include <strix/net/object/Number.h>
#include <strix/net/object/ObjectAdapter.h>
#include <memory>

namespace strix { namespace client { namespace ingame { namespace network { namespace data {

/**
 *  Container for the properties of a room, with several known 
 *  property names alongside additional custom properties
 *  
 *  The custom properties of this container cannot be used for searching and are implementation
 *  defined. Use the key and string properties as limited custom properties that can be searched
 */
class RoomProperties
{
public:
	RoomProperties()
		: m_capacity(4), m_state(0), m_isJoinable(true),
		  m_key1(0.0), m_key2(0.0), m_key3(0.0), m_key4(0.0),
		  m_key5(0.0), m_key6(0.0), m_key7(0.0), m_key8(0.0)
	{
	}

	/**
	 *  Get the room name
	 *  @returns	The room name
	 */
	const std::string &GetName() const { return m_name; }

	/**
	 *  Set the room name
	 *  @param	name	The room name
	 */
	void SetName(std::string name) { m_name = std::move(name); }

	/**
	 *  Get the capacity of this room
	 *  @returns	The capacity
	 */
	int GetCapacity() const { return m_capacity; }

	/**
	 *  Set the capacity of this room
	 *  @param	capacity	The capacity
	 */
	void SetCapacity(int capacity) { m_capacity = capacity; }

	/**
	 *  Get this room's password
	 *  @returns	The room's password
	 */
	const std::string &GetPassword() const { return m_password; }

	/**
	 *  Set this room's password
	 *  @param	password	The room's password
	 */
	void SetPassword(std::string password) { m_password = std::move(password); }

	/**
	 *  Get the state of the room (implementation defined)
	 *  @returns	The state
	 */
	int GetState() const { return m_state; }

	/**
	 *  Set the state of the room (implementation defined)
	 *  @param	state	The state
	 */
	void SetState(int state) { m_state = state; }

	/**
	 *  Get if the room is joinable
	 *  @returns	True if the room can be joined
	 */
	bool GetIsJoinable() const { return m_isJoinable; }

	/**
	 *  Set if the room is joinable
	 *  @param	isJoinable	True if joinable
	 */
	void SetIsJoinable(bool isJoinable) { m_isJoinable = isJoinable; }

	/**
	 *  Get customizable key
	 *  @returns	key
	 */
	double GetKey1() const { return m_key1; }

	/**
	 *  Set customizable key
	 *  @param	key1	key
	 */
	void SetKey1(double key1) { m_key1 = key1; }

	/**
	 *  Get customizable key
	 *  @returns	key2
	 */
	double GetKey2() const { return m_key2; }

	/**
	 *  Set customizable key
	 *  @param	key2	key
	 */
	void SetKey2(double key2) { m_key2 = key2; }

	/**
	 *  Get customizable key
	 *  @returns	key3
	 */
	double GetKey3() const { return m_key3; }

	/**
	 *  Set customizable key
	 *  @param	key3	key
	 */
	void SetKey3(double key3) { m_key3 = key3; }

	/**
	 *  Get customizable key
	 *  @returns	key4
	 */
	double GetKey4() const { return m_key4; }

	/**
	 *  Set customizable key
	 *  @param	key4	key
	 */
	void SetKey4(double key4) { m_key4 = key4; }

	/**
	 *  Get customizable key
	 *  @returns	key5
	 */
	double GetKey5() const { return m_key5; }

	/**
	 *  Set customizable key
	 *  @param	key5	key
	 */
	void SetKey5(double key5) { m_key5 = key5; }

	/**
	 *  Get customizable key
	 *  @returns	key6
	 */
	double GetKey6() const { return m_key6; }

	/**
	 *  Set customizable key
	 *  @param	key6	key
	 */
	void SetKey6(double key6) { m_key6 = key6; }

	/**
	 *  Get customizable key
	 *  @returns	key7
	 */
	double GetKey7() const { return m_key7; }

	/**
	 *  Set customizable key
	 *  @param	key7	key
	 */
	void SetKey7(double key7) { m_key7 = key7; }

	/**
	 *  Get customizable key
	 *  @returns	key8
	 */
	double GetKey8() const { return m_key8; }

	/**
	 *  Set customizable key
	 *  @param	key8	key
	 */
	void SetKey8(double key8) { m_key8 = key8; }

	/**
	 *  Get string key
	 *  @returns	key
	 */
	const std::string &GetStringKey() const { return m_stringKey; }

	/**
	 *  Set string key
	 *  @param	stringKey	key
	 */
	void SetStringKey(std::string stringKey) { m_stringKey = std::move(stringKey); }

	/**
	 *  Set this room's customizable properties
	 *  @param	properties	Map of strings (property names) to objects (values)
	 */
	void SetPropertiesMap(net::object::ObjectMap properties) { m_properties = properties; }

	/**
	 *  Get this room's customizable properties
	 *  @returns	Map of strings (property names) to objects (values)
	 */
	const net::object::ObjectMap &GetPropertiesMap() const { return m_properties; }

	/**
	 *  Set a property in the custom properties map
	 *  @param	key	The name of the property
	 *  @param	value	The value of the property
	 */
	void SetProperty(std::string key, net::object::ObjectAdapter value)
	{
		m_properties->emplace(std::make_pair(net::object::ObjectAdapter(key), std::move(value)));
	}

	/**
	 *  Get the given properties value
	 *  @param	key	The name of the property
	 *  @return	The value of the property
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
	 *  Get the known properties and custom properties as a map representation.
	 *  Contains the following keys: 
	 *  "name", 
	 *  "capacity",
	 *  "password",
	 *  "state", 
	 *  "isJoinable", 
	 *  "key1", 
	 *  "key2", 
	 *  "key3", 
	 *  "key4",
	 *  "key5", 
	 *  "key6", 
	 *  "key7", 
	 *  "key8", 
	 *  "stringKey", 
	 *  "properties"
	 *  @returns	The map
	 */
	std::map<std::string, strix::net::object::ObjectPtr> ToMap() const
	{
		std::map<std::string, strix::net::object::ObjectPtr> map = {
			{"name", net::object::ObjectAdapter(m_name)},
			{"capacity", net::object::ObjectAdapter(m_capacity)},
			{"state", net::object::ObjectAdapter(m_state)},
			{"isJoinable", net::object::ObjectAdapter(m_isJoinable)},
			{"key1", net::object::ObjectAdapter(m_key1)},
			{"key2", net::object::ObjectAdapter(m_key2)},
			{"key3", net::object::ObjectAdapter(m_key3)},
			{"key4", net::object::ObjectAdapter(m_key4)},
			{"key5", net::object::ObjectAdapter(m_key5)},
			{"key6", net::object::ObjectAdapter(m_key6)},
			{"key7", net::object::ObjectAdapter(m_key7)},
			{"key8", net::object::ObjectAdapter(m_key8)},
			{"stringKey", net::object::ObjectAdapter(m_stringKey)},
			{"properties", std::make_shared<net::object::ObjectMap>(m_properties)}
		};

		if (!m_password.empty())
		{
			map["password"] = net::object::ObjectAdapter(m_password);
		}

		return map;
	}

	/**
	 *  Sets this room's properties from a map of properties. The valid names and types are
	 *  "name": StringObject, 
	 *  "capacity": IntegerObject,
	 *  "password": StringObject,
	 *  "state": IntegerObject, 
	 *  "isJoinable": BooleanObject, 
	 *  "key1": DoubleObject, 
	 *  "key2": DoubleObject, 
	 *  "key3": DoubleObject, 
	 *  "key4": DoubleObject, 
	 *  "key5": DoubleObject, 
	 *  "key6": DoubleObject, 
	 *  "key7": DoubleObject, 
	 *  "key8": DoubleObject, 
	 *  "stringKey": StringObject, 
	 *  "properties": ObjectMap
	 */
	void FromMap(const std::map<std::string, strix::net::object::ObjectPtr> &propertiesMap)
	{
		auto it = propertiesMap.find("name");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::StringObject>())
			m_name = std::static_pointer_cast<net::object::StringObject>(it->second)->Get();

		it = propertiesMap.find("capacity");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::IntegerObject>())
			m_capacity = std::static_pointer_cast<net::object::IntegerObject>(it->second)->Get();

		it = propertiesMap.find("password");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::StringObject>())
			m_password = std::static_pointer_cast<net::object::StringObject>(it->second)->Get();

		it = propertiesMap.find("state");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::IntegerObject>())
			m_state = std::static_pointer_cast<net::object::IntegerObject>(it->second)->Get();

		it = propertiesMap.find("isJoinable");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::BooleanObject>())
			m_isJoinable = std::static_pointer_cast<net::object::BooleanObject>(it->second)->Get();

		it = propertiesMap.find("key1");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::DoubleObject>())
			m_key1 = std::static_pointer_cast<net::object::DoubleObject>(it->second)->Get();

		it = propertiesMap.find("key2");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::DoubleObject>())
			m_key2 = std::static_pointer_cast<net::object::DoubleObject>(it->second)->Get();

		it = propertiesMap.find("key3");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::DoubleObject>())
			m_key3 = std::static_pointer_cast<net::object::DoubleObject>(it->second)->Get();

		it = propertiesMap.find("key4");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::DoubleObject>())
			m_key4 = std::static_pointer_cast<net::object::DoubleObject>(it->second)->Get();

		it = propertiesMap.find("key5");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::DoubleObject>())
			m_key5 = std::static_pointer_cast<net::object::DoubleObject>(it->second)->Get();

		it = propertiesMap.find("key6");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::DoubleObject>())
			m_key6 = std::static_pointer_cast<net::object::DoubleObject>(it->second)->Get();

		it = propertiesMap.find("key7");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::DoubleObject>())
			m_key7 = std::static_pointer_cast<net::object::DoubleObject>(it->second)->Get();

		it = propertiesMap.find("key8");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::DoubleObject>())
			m_key8 = std::static_pointer_cast<net::object::DoubleObject>(it->second)->Get();

		it = propertiesMap.find("stringKey");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::StringObject>())
			m_stringKey = std::static_pointer_cast<net::object::StringObject>(it->second)->Get();

		it = propertiesMap.find("properties");
		if (it != propertiesMap.end() && it->second->InstanceOf<net::object::ObjectMap>())
			m_properties = std::static_pointer_cast<net::object::ObjectMap>(it->second)->Get();
	}

private:
	std::string m_name;
	int m_capacity;
	std::string m_password;
	int m_state;
	bool m_isJoinable;
	double m_key1;
	double m_key2;
	double m_key3;
	double m_key4;
	double m_key5;
	double m_key6;
	double m_key7;
	double m_key8;
	std::string m_stringKey;
	net::object::ObjectMap m_properties;
};

typedef std::shared_ptr<RoomProperties> RoomPropertiesPtr;

} } } } }
