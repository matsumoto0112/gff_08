#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/MetaClass.h>
#include <strix/net/object/MetaClassT.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace util {

/**
 *  Utility class for Strix implemented reflection
 */
class ReflectionUtil
{
public:
	static const std::string PROPERTY_PREFIX;

	/**
	 *  Set an Object's properties from a property map. Will log to Strix if properties could not be set
	 *  
	 *  @param  destination	The Object to set properties for
	 *  @param  properties	The property map
	 */
	static void SetPropertiesUsingMap(const net::object::ObjectPtr &destination, std::map<std::string, strix::net::object::ObjectPtr> properties);

	/**
	 *  Creates an instance of class T with the given properties
	 *  
	 *  @param  properties	The property map
	 *  @returns	A pointer to the new instance
	 */
	template<class T>
	static std::shared_ptr<T> CreateClassInstance(const std::map<std::string, strix::net::object::ObjectPtr> &properties)
	{
		std::shared_ptr<T> obj = net::object::MetaClassT<T>::Create();
		SetPropertiesUsingMap(obj, properties);
		return obj;
	}

	/**
	 *  Creates an instance of a class with the given properties
	 *
	 *  @param  type    The type of object to instantiate
	 *  @param  properties	The property map
	 *  @returns	A pointer to the new instance
	 */
	static net::object::ObjectPtr CreateClassInstance(const net::object::MetaClass &type, const std::map<std::string, strix::net::object::ObjectPtr> &properties);
private:
	static bool SetFieldValue(const net::object::ObjectPtr &destination, const net::object::MetaClass &destClass, const std::string &fieldName, const net::object::ObjectPtr &value);
};

} } } }
