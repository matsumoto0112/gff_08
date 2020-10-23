#pragma once

#include <memory>
#include <type_traits>

namespace strix { namespace net { namespace io {
	class Decoder;
	class Encoder;
} } }

namespace strix { namespace net { namespace object {

class MetaClass;

template <typename T, bool IsObject>
class MetaClassT;

namespace detail {
	struct MetaClassHelper {
		template <class T>
		static auto HasInitMetaClassMethod(int)->std::integral_constant<bool, std::is_same<void, decltype(T::_InitMetaClass(*static_cast<typename T::MetaClassType*>(nullptr)))>::value>;

		template <class>
		static auto HasInitMetaClassMethod(...)->std::false_type;
	};
}

template <typename T>
struct HasInitMetaClassMethod : decltype(detail::MetaClassHelper::HasInitMetaClassMethod<T>(0)) {};

class Object
{
public:
	typedef MetaClassT<Object, true> MetaClassType;
	friend MetaClassType;

	static const MetaClass &s_GetMetaClass();

	virtual const MetaClass &GetMetaClass() const;

	bool InstanceOf(const MetaClass &metaClass) const;

	template <class Class>
	bool InstanceOf() const;

	virtual int Compare(const Object &rhs) const;

	virtual ~Object();
	
	bool operator<(const Object &rhs) const {
		return Compare(rhs) < 0;
	}

	bool operator>(const Object &rhs) const {
		return Compare(rhs) > 0;
	}

	bool operator>=(const Object &rhs) const {
		return !operator<(rhs);
	}

	bool operator<=(const Object &rhs) const {
		return !operator>(rhs);
	}

	bool operator==(const Object &rhs) const {
		return Compare(rhs) == 0;
	}

	bool operator!=(const Object &rhs) const {
		return Compare(rhs) != 0;
	}

protected:
	Object();

private: 
	friend struct detail::MetaClassHelper;

	static Object *_Create() {
		return NULL;
	}
	
	static void _InitMetaClass(MetaClassType &metaClass);
};

typedef std::shared_ptr<Object> ObjectPtr;

} } }
