#pragma once

#include <strix/net/object/MetaClass.h>
#include <strix/net/logging/Logger.h>

#include <string>
#include <iostream>
#include <set>
#include <list>

namespace strix { namespace net { namespace object {

template <class T>
class MetaClassBaseT : public MetaClass
{
public:
	template <typename ArgType>
	void AddProperty(const std::string &name, const ArgType *offset);

	template <typename VarType, typename GetterFuncType, typename SetterFuncType>
	void AddAccessorProperty(const std::string &name, GetterFuncType getterFunction, SetterFuncType setterFunction);

	template <typename VarType, typename ArgType>
	void AddTypedProperty(const std::string &name, const ArgType *offset);
};

class MetaClassRegistryLogger
{
public:
	STRIX_NET_LOGGER("strix.net.object");
};

template <typename T>
class TypeNameFactory
{
public:
	static std::string GetTypeName(bool shouldInitializeMetaclass)
	{
		if (shouldInitializeMetaclass)
		{
			return MetaClassT<T, HasInitMetaClassMethod<T>::value>::Get().GetName();
		}
		else
		{
			STRIX_NET_LOG_WARNING_(MetaClassRegistryLogger::__strix_net_logger(), "Unknown type id, please specify STRIX_CLASS_ID.");
			return "unknown-type";
		}
	}
};

template <typename T, bool IsObject = HasInitMetaClassMethod<T>::value>
class MetaClassT {};

template <typename T>
class MetaClassT<T, true> : public MetaClassBaseT<T>
{
public:
	static const MetaClassT &Get() {
		static const MetaClassT<T, true> instance;
		return instance;
	}

	void *Create() const override {
		return T::_Create();
	}

private:
	MetaClassT() {
		T::_InitMetaClass(*this);
		if (this->GetClassId() == 0)
		{
			MetaClass::SetClassId(TypeNameFactory<T>::GetTypeName(false));
		}

		if (this->GetClassId() != 0)
		{
			if (!MetaClass::Register(*this, MetaClass::GetClassId()))
			{
				STRIX_NET_LOG_WARNING_(MetaClassRegistryLogger::__strix_net_logger(), "Could not register metaclass for id " << this->GetClassId()
					<< ", name "<< this->GetName() << ", display name " << this->GetDisplayName());
			}
		}
		else
		{
			STRIX_NET_LOG_WARNING_(MetaClassRegistryLogger::__strix_net_logger(), "Class id not generated for class " << this->GetName()
				<< ", display name " << this->GetDisplayName());
		}
	}
};

template <typename T>
class MetaClassT<T, false> : public MetaClassBaseT<T>
{
public:
	static const MetaClassT &Get() {
		static const MetaClassT<T, false> instance;
		return instance;
	}

	void *Create() const override {
		return new T();
	}

private:
	MetaClassT() {
		MetaClass::SetClassId(TypeNameFactory<T>::GetTypeName(false));
		MetaClass::Register(*this, MetaClass::GetClassId());
	}
};

template <typename T>
bool MetaClass::Register(ClassId classId) {
	return Register(MetaClassT<T>::Get(), classId);
}

#define _STRIX_CLASS_FACTORY_FUNC(Class)                                     \
	static _ThisType *_Create() {                                           \
		return new _ThisType();                                             \
	}                                                                       \

#define _STRIX_CLASS_FACTORY_FUNC_NULL(Class)                                \
	static _ThisType *_Create() {                                           \
		return NULL;                                                        \
	}                                                                       \

#define _STRIX_CLASS_BEGIN(Class, FactoryMethod, Override)                  \
private:                                                                    \
	typedef Class _ThisType;                                                \
	friend struct strix::net::object::detail::MetaClassHelper;              \
public:                                                                     \
	typedef strix::net::object::MetaClassT<_ThisType, true> MetaClassType;  \
	friend MetaClassType;                                                   \
	static const strix::net::object::MetaClass &s_GetMetaClass() {          \
		return MetaClassType::Get();            \
	}                                                                       \
	const strix::net::object::MetaClass &GetMetaClass() const Override {    \
		return s_GetMetaClass();                                            \
	}                                                                       \
private:                                                                    \
	FactoryMethod(Class)                                                    \
	static void _InitMetaClass(MetaClassType &metaClass) {                  \
		metaClass.SetDisplayName(#Class);                                   \

#define STRIX_CLASS_BEGIN(Class, SuperClass)                                 \
		_STRIX_CLASS_BEGIN(Class, _STRIX_CLASS_FACTORY_FUNC, override)       \
		STRIX_CLASS_SUPER(SuperClass);                                       \

#define STRIX_CLASS_BEGIN_ABSTRACT(Class, SuperClass)                        \
		_STRIX_CLASS_BEGIN(Class, _STRIX_CLASS_FACTORY_FUNC_NULL, override)  \
		STRIX_CLASS_SUPER(SuperClass);                                       \

#define STRIX_CLASS_BEGIN_BASE(Class)                                        \
		_STRIX_CLASS_BEGIN(Class, _STRIX_CLASS_FACTORY_FUNC, )               \

#define STRIX_CLASS_BEGIN_BASE_ABSTRACT(Class)                               \
		_STRIX_CLASS_BEGIN(Class, _STRIX_CLASS_FACTORY_FUNC_NULL, )          \

#define STRIX_CLASS_ID(Id)                                                   \
		metaClass.SetClassId(Id);

#define STRIX_CLASS_SUPER(SuperClass)                                        \
		metaClass.AddSuperClass(&strix::net::object::MetaClassT<SuperClass>::Get(), (size_t)(static_cast<SuperClass*>((_ThisType*)1)) - 1);


#define STRIX_PROPERTY(Variable)                                       \
		metaClass.AddProperty(#Variable, &((_ThisType*)0)->Variable);

#define STRIX_PROPERTY_TYPED(Variable, VarType)                        \
		metaClass.AddTypedProperty<VarType>(#Variable, &((_ThisType*)0)->Variable);

#define STRIX_PROPERTY_ACCESSOR(Name, VarType, Getter, Setter)         \
		metaClass.AddAccessorProperty<VarType>(#Name, Getter, Setter);

#define STRIX_CLASS_END()                                              \
		metaClass.SortPropertyAccessors();									\
	}												                        \
public:                                                                     \


#define _STRIX_CLASS_DEFINITION(...) __VA_ARGS__ STRIX_CLASS_END()

#define STRIX_CLASS(Class, SuperClass)                                 \
	STRIX_CLASS_BEGIN(Class, SuperClass)                               \
	_STRIX_CLASS_DEFINITION

#define STRIX_ABSTRACT_CLASS(Class, SuperClass)                        \
	STRIX_CLASS_BEGIN_ABSTRACT(Class, SuperClass)                      \
	_STRIX_CLASS_DEFINITION                                       


#define STRIX_BASE_CLASS(Class)                                        \
	STRIX_CLASS_BEGIN_BASE(Class)                                      \
	_STRIX_CLASS_DEFINITION                                       

#define STRIX_BASE_ABSTRACT_CLASS(Class)                               \
	STRIX_CLASS_BEGIN_BASE_ABSTRACT(Class)                             \
	_STRIX_CLASS_DEFINITION           


template <>
class TypeNameFactory<bool>
{
public:
	static std::string GetTypeName(bool)
	{
		return "bool";
	}
};

template <>
class TypeNameFactory<int8_t>
{
public:
	static std::string GetTypeName(bool)
	{
		return "int8_t";
	}
};

template <>
class TypeNameFactory<uint8_t>
{
public:
	static std::string GetTypeName(bool)
	{
		return "uint8_t";
	}
};

template <>
class TypeNameFactory<short>
{
public:
	static std::string GetTypeName(bool)
	{
		return "short";
	}
};

template <>
class TypeNameFactory<unsigned short>
{
public:
	static std::string GetTypeName(bool)
	{
		return "unsigned short";
	}
};

template <>
class TypeNameFactory<int>
{
public:
	static std::string GetTypeName(bool)
	{
		return "int";
	}
};

template <>
class TypeNameFactory<unsigned int>
{
public:
	static std::string GetTypeName(bool)
	{
		return "unsigned int";
	}
};

template <>
class TypeNameFactory<long>
{
public:
	static std::string GetTypeName(bool)
	{
		return "long";
	}
};

template <>
class TypeNameFactory<unsigned long>
{
public:
	static std::string GetTypeName(bool)
	{
		return "unsigned long";
	}
};

template <>
class TypeNameFactory<long long>
{
public:
	static std::string GetTypeName(bool)
	{
		return "long long";
	}
};

template <>
class TypeNameFactory<unsigned long long>
{
public:
	static std::string GetTypeName(bool)
	{
		return "unsigned long long";
	}
};

template <>
class TypeNameFactory<float>
{
public:
	static std::string GetTypeName(bool)
	{
		return "float";
	}
};

template <>
class TypeNameFactory<double>
{
public:
	static std::string GetTypeName(bool)
	{
		return "double";
	}
};

template <>
class TypeNameFactory<char>
{
public:
	static std::string GetTypeName(bool)
	{
		return "char";
	}
};

template <>
class TypeNameFactory<std::string>
{
public:
	static std::string GetTypeName(bool)
	{
		return "std::string";
	}
};

template <typename T>
class TypeNameFactory<std::vector<T>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "std::vector<" + TypeNameFactory<T>::GetTypeName(true) + ">";
	}
};

template <typename T>
class TypeNameFactory<std::list<T>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "std::list<" + TypeNameFactory<T>::GetTypeName(true) + ">";
	}
};

template <typename TKey, typename TComparator>
class TypeNameFactory<std::set<TKey, TComparator>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "std::set<" + TypeNameFactory<TKey>::GetTypeName(true) + ">";
	}
};

template <typename TKey, typename TValue, typename TComparator>
class TypeNameFactory<std::map<TKey, TValue, TComparator>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "std::map<" + TypeNameFactory<TKey>::GetTypeName(true)
		+ ", " + TypeNameFactory<TValue>::GetTypeName(true) + ">";
	}
};

template <typename T>
class TypeNameFactory<std::shared_ptr<T>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "std::shared_ptr<" + TypeNameFactory<T>::GetTypeName(true) + ">";
	}
};

template <typename T>
class TypeNameFactory<T*>
{
public:
	static std::string GetTypeName(bool)
	{
		return TypeNameFactory<T>::GetTypeName(true) + "*";
	}
};

template <typename T>
class TypeNameFactory<const T*>
{
public:
	static std::string GetTypeName(bool)
	{
		return "const " + TypeNameFactory<T>::GetTypeName(true) + "*";
	}
};

template <typename T>
class TypeNameFactory<T&>
{
public:
	static std::string GetTypeName(bool)
	{
		return TypeNameFactory<T>::GetTypeName(true) + "&";
	}
};

template <typename T>
class TypeNameFactory<const T&>
{
public:
	static std::string GetTypeName(bool)
	{
		return "const " + TypeNameFactory<T>::GetTypeName(true) + "&";
	}
};

template <>
class TypeNameFactory<MetaClass>
{
public:
	static std::string GetTypeName(bool)
	{
		return "strix::net::object::MetaClass";
	}
};

template <typename T>
class TypeNameFactory<MetaClassT<T>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "strix::net::object::MetaClassT<" + TypeNameFactory<T>::GetTypeName(true) + ">";
	}
};

} } }
