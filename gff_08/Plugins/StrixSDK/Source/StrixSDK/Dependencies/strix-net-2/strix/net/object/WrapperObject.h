#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/PredefinedClassId.h>

#include <chrono>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace strix { namespace net { namespace object {

class WrapperObject : public Object
{
public:
	STRIX_ABSTRACT_CLASS(WrapperObject, Object)
	(
	)

	virtual const void * GetRaw() const = 0;
};

template <typename T>
class WrapperObjectT : public WrapperObject
{
	STRIX_ABSTRACT_CLASS(WrapperObjectT, WrapperObject)
	(
		STRIX_PROPERTY(m_value)
	)

	WrapperObjectT() : m_value() {} 
	WrapperObjectT(const WrapperObjectT<T> &other) : m_value(other.m_value) {}
	WrapperObjectT(WrapperObjectT<T> &&other) = default;
	WrapperObjectT(const T &value) : m_value(value) {}
	WrapperObjectT(T &&value) : m_value(std::move(value)) {}

	T &Get() {
		return m_value;
	}

	const T &Get() const {
		return m_value;
	}

	const void *GetRaw() const override
	{
		return &m_value;
	}

	void Set(const T &value) {
		m_value = value;
	}

	operator T() const {
		return m_value;
	}

	T &operator*() {
		return m_value;
	}

	const T &operator*() const {
		return m_value;
	}

	T *operator->() {
		return &m_value;
	}

	const T *operator->() const {
		return &m_value;
	}

protected:
	T m_value;
};

template <typename T>
class StructWrapperObjectT : public Object
{
	STRIX_ABSTRACT_CLASS(StructWrapperObjectT, Object)
	(
	)

	StructWrapperObjectT() {}

	virtual T Get() const = 0;
};

template <typename T, int _ClassId>
class WrapperObjectImpl : public WrapperObjectT<T>
{
public:
	STRIX_CLASS(WrapperObjectImpl, WrapperObjectT<T>)
	(
		STRIX_CLASS_ID(_ClassId)
	)

	typedef T ValueType;

	WrapperObjectImpl() = default;
	WrapperObjectImpl(const WrapperObjectImpl<T, _ClassId> &other) : WrapperObjectT<T>(other) {};
	WrapperObjectImpl(WrapperObjectImpl<T, _ClassId> &&other) = default;
	WrapperObjectImpl(const T &value) : WrapperObjectT<T>(value) {};
	WrapperObjectImpl(T &&value) : WrapperObjectT<T>(std::move(value)) {};

	virtual ~WrapperObjectImpl() = default;

	WrapperObjectImpl<T, _ClassId> &operator=(const T &value) {
		WrapperObjectT<T>::m_value = value;
		return *this;
	}
	
	WrapperObjectImpl<T, _ClassId> &operator=(T &&value) {
		WrapperObjectT<T>::m_value = std::move(value);
		return *this;
	}

	WrapperObjectImpl<T, _ClassId> &operator=(const WrapperObjectImpl<T, _ClassId> &other) {
		WrapperObjectT<T>::m_value = other.m_value;
		return *this;
	}
	
	WrapperObjectImpl<T, _ClassId> &operator=(WrapperObjectImpl<T, _ClassId> &&other) = default;

	bool operator<(const WrapperObjectImpl<T, _ClassId> &rhs) const {
		return WrapperObjectT<T>::m_value < rhs.m_value;
	}

	bool operator<=(const WrapperObjectImpl<T, _ClassId> &rhs) const {
		return WrapperObjectT<T>::m_value <= rhs.m_value;
	}

	bool operator>(const WrapperObjectImpl<T, _ClassId> &rhs) const {
		return WrapperObjectT<T>::m_value > rhs.m_value;
	}

	bool operator>=(const WrapperObjectImpl<T, _ClassId> &rhs) const {
		return WrapperObjectT<T>::m_value >= rhs.m_value;
	}

	bool operator==(const WrapperObjectImpl<T, _ClassId> &rhs) const {
		return WrapperObjectT<T>::m_value == rhs.m_value;
	}

	bool operator!=(const WrapperObjectImpl<T, _ClassId> &rhs) const {
		return WrapperObjectT<T>::m_value != rhs.m_value;
	}

	int Compare(const Object &rhs) const override {

		const MetaClass &metaClass = GetMetaClass();
		const MetaClass &metaClass2 = rhs.GetMetaClass();
	
		if (&metaClass > &metaClass2)
			return 1;
		if (&metaClass < &metaClass2)
			return -1;

		const WrapperObjectImpl<T, _ClassId> &v = static_cast<const WrapperObjectImpl<T, _ClassId> &>(rhs);
		
		if (WrapperObjectT<T>::m_value > v.m_value)
			return 1;
		if (WrapperObjectT<T>::m_value < v.m_value)
			return -1;

		return 0;
	}
};

struct PointerValueComparator
{
	template <typename T>
	bool operator()(const T &lhs, const T &rhs) const {
		return *lhs < *rhs;
	}
};

typedef WrapperObjectImpl<bool, static_cast<int>(PredefinedClassId::Boolean)> BooleanObject;
typedef WrapperObjectImpl<char, static_cast<int>(PredefinedClassId::Character)> CharacterObject;
typedef WrapperObjectImpl<std::string, static_cast<int>(PredefinedClassId::String)> StringObject;
typedef WrapperObjectImpl<std::vector<uint8_t>, static_cast<int>(PredefinedClassId::Binary)> BinaryObject;
typedef WrapperObjectImpl<std::chrono::system_clock::time_point, static_cast<int>(PredefinedClassId::Date)> DateObject;
typedef WrapperObjectImpl<std::vector<ObjectPtr>, static_cast<int>(PredefinedClassId::Vector)> ObjectVector;
typedef WrapperObjectImpl<std::list<ObjectPtr>, static_cast<int>(PredefinedClassId::List)> ObjectList;
typedef WrapperObjectImpl<std::set<ObjectPtr, PointerValueComparator>, static_cast<int>(PredefinedClassId::Set)> ObjectSet;
typedef WrapperObjectImpl<std::map<ObjectPtr, ObjectPtr, PointerValueComparator>, static_cast<int>(PredefinedClassId::Map)> ObjectMap;

template <>
class TypeNameFactory<WrapperObject>
{
public:
	static std::string GetTypeName(bool)
	{
		return "strix::net::object::WrapperObject";
	}
};

template <typename T>
class TypeNameFactory<WrapperObjectT<T>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "strix::net::object::WrapperObjectT<"
		+ TypeNameFactory<T>::GetTypeName(true) + ">";
	}
};

template <typename T>
class TypeNameFactory<StructWrapperObjectT<T>>
{
public:
	static std::string GetTypeName(bool)
	{
		return "strix::net::object::StructWrapperObjectT<"
			+ TypeNameFactory<T>::GetTypeName(true) + ">";
	}
};

template <>
class TypeNameFactory<std::chrono::system_clock::time_point>
{
public:
	static std::string GetTypeName(bool)
	{
		return "std::chrono::system_clock::time_point";
	}
};

} } }
