#pragma once

#include <strix/net/logging/Logger.h>
#include <strix/net/object/Number.h>
#include <strix/net/object/ObjectAdapter.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace util {

/**
 *  Converts between Strix Objects and other types
 */
class ObjectConverter
{
	STRIX_NET_LOGGER("strix.net.object");
	template<typename T> struct is_shared_ptr : std::false_type {};
	template<typename T> struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

public:
	// T is an Object value
	template <typename T>
	static std::enable_if_t<!is_shared_ptr<T>::value && std::is_base_of<net::object::Object, T>::value, bool>
	TryConvertObjectToValue(net::object::ObjectPtr object, T &out)
	{
		if (object->InstanceOf<T>())
		{
			out = *(std::static_pointer_cast<T>(object));
			return true;
		}

		return false;
	}

	// T is a Wrapper/Number value
	template <typename T>
	static std::enable_if_t<!is_shared_ptr<T>::value && !std::is_base_of<net::object::Object, T>::value, bool>
	TryConvertObjectToValue(net::object::ObjectPtr object, T &out)
	{
		if (object->InstanceOf<net::object::NumberT<T>>())
		{
			out = std::static_pointer_cast<net::object::NumberT<T>>(object)->Get();
			return true;
		}
		if (object->InstanceOf<net::object::WrapperObjectT<T>>())
		{
			out = std::static_pointer_cast<net::object::WrapperObjectT<T>>(object)->Get();
			return true;
		}
		if (object->InstanceOf<net::object::StructWrapperObjectT<T>>())
		{
			out = std::static_pointer_cast<net::object::StructWrapperObjectT<T>>(object)->Get();
			return true;
		}

		return false;
	}
	
	// T is a shared_ptr derived from ObjectPtr
	template <typename T>
	static std::enable_if_t<is_shared_ptr<T>::value && std::is_base_of<net::object::Object, typename T::element_type>::value, bool>
	TryConvertObjectToValue(net::object::ObjectPtr object, T &out)
	{
		if (object->InstanceOf<typename T::element_type>())
		{
			out = std::static_pointer_cast<typename T::element_type>(object);
			return true;
		}

		return false;
	}
	
	// T is a shared_ptr not derived from ObjectPtr
	template <typename T>
	static std::enable_if_t<is_shared_ptr<T>::value && !std::is_base_of<net::object::Object, typename T::element_type>::value, bool>
	TryConvertObjectToValue(net::object::ObjectPtr object, T &out)
	{
		STRIX_NET_LOG_DEBUG("Conversion from ObjectPtr to shared_ptr<T> where T does not derive Object isn't supported.");
		return false;
	}

	template <typename T>
	static T ConvertObjectToValue(net::object::ObjectPtr object)
	{
		T out;
		if (!ObjectConverter::TryConvertObjectToValue(object, out))
		{
			STRIX_NET_LOG_WARNING("Could not convert object to value, types do not match");
		}
		return out;
	}

	template <typename T>
	static net::object::ObjectPtr ConvertValueToObject(const T &value)
	{
		return net::object::ObjectAdapter(value);
	}

	template <typename T>
	static net::object::ObjectPtr ConvertValueToObject(T &&value)
	{
		return net::object::ObjectAdapter(value);
	}
};

} } } }
