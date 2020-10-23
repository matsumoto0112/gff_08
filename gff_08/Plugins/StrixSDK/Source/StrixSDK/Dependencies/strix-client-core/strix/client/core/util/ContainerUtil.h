#pragma once

#include <strix/net/object/ObjectAdapter.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace util {

/**
 *  Utility class for constructing containers of Strix Objects
 */
class ContainerUtil
{
public:

	/**
	 *  Creates a vector of type T from a Strix ObjectList
	 *  
	 *  @param  objectList	The list to cast from
	 *  @returns	A vector representing the list
	 */
	template <typename T>
	static std::vector<std::shared_ptr<T> > CastObjectList(const strix::net::object::ObjectList &objectList)
	{
		std::vector<std::shared_ptr<T> > result;
		result.reserve(objectList.Get().size());

		for (const strix::net::object::ObjectPtr &object : objectList.Get())
		{
			if (object->InstanceOf<T>())
			{
				result.emplace_back(std::static_pointer_cast<T>(object));
			}
		}

		return result;
	}

	/**
	 *  Creates an ObjectMap from a list of key value pairs
	 *  
	 *  @param  keyValues	The pairs to create the map from
	 *  @returns	An ObjectMap of key value pairs
	 */
	static net::object::ObjectMap CreateObjectMap(std::initializer_list<std::pair<net::object::ObjectAdapter, net::object::ObjectAdapter>> keyValues)
	{
		net::object::ObjectMap map;
		for (const auto &keyValue : keyValues)
		{
			map.Get()[keyValue.first] = keyValue.second;
		}
		return map;
	}

	/**
	 *  Creates an ObjectMap from a list of key value pairs
	 *
	 *  @param  keyValues	The pairs to create the map from
	 *  @returns	An ObjectMap of key value pairs
	 */
	static std::shared_ptr<net::object::ObjectMap> CreateObjectMapPtr(std::initializer_list<std::pair<net::object::ObjectAdapter, net::object::ObjectAdapter>> keyValues)
	{
		std::shared_ptr<net::object::ObjectMap> map = std::make_shared<net::object::ObjectMap>();
		for (const auto &keyValue : keyValues)
		{
			map->Get()[keyValue.first] = keyValue.second;
		}
		return map;
	}

	/**
	 *  Creates an ObjectMap from a list of key value pairs
	 *
	 *  @param  keyValues	The pairs to create the map from
	 *  @returns	An ObjectMap of key value pairs
	 */
	static std::map<std::string, net::object::ObjectPtr> CreateStringObjectMap(std::initializer_list<std::pair<std::string, net::object::ObjectAdapter>> keyValues)
	{
		std::map<std::string, net::object::ObjectPtr> map;
		for (const auto &keyValue : keyValues)
		{
			map[keyValue.first] = keyValue.second;
		}
		return map;
	}
};

} } } }
