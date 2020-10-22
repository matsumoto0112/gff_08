#pragma once

#include <strix/net/serialization/serializer/DynamicSerializerImpl.h>

#include <memory>
#include <typeinfo>

namespace strix { namespace net { namespace object {

class PropertyAccessor
{
public:
	virtual ~PropertyAccessor() { }

	virtual void *Get(void *obj) = 0;
	virtual void Set(void *obj, const void *arg) = 0;
	virtual serialization::serializer::DynamicSerializer &GetSerializer() = 0;
};

typedef std::shared_ptr<PropertyAccessor> PropertyAccessorPtr;

template <typename VarType>
class AbstractPropertyAccessor : public PropertyAccessor
{
public:
	typedef typename serialization::serializer::DynamicSerializerImpl<VarType> SerializerType;

	serialization::serializer::DynamicSerializer &GetSerializer() override {
		return m_serializer;
	}

protected:
	SerializerType m_serializer;
};

template <typename VarType>
class DefaultPropertyAccessor : public AbstractPropertyAccessor<VarType>
{
public:
	DefaultPropertyAccessor(int offset) : m_offset(offset) {}

	void *Get(void *obj) override {
		return (VarType*)((size_t)obj + m_offset);
	}

	void Set(void *obj, const void *arg) override {
		*(VarType*)((size_t)obj + m_offset) = *(VarType*)arg;
	}

private:
	int m_offset;
};

template <typename VarType, typename InternalType>
class TypedPropertyAccessor : public AbstractPropertyAccessor<VarType>
{
public:
	TypedPropertyAccessor(int offset) : m_offset(offset) {}

	void *Get(void *obj) override {
		return (InternalType*)((size_t)obj + m_offset);
	}

	void Set(void *obj, const void *arg) override {
		*(InternalType*)((size_t)obj + m_offset) = static_cast<InternalType>(*(VarType*)arg);
	}
	
private:
	int m_offset;
};

template <class T, typename VarType>
class WrapperPropertyAccessor : public AbstractPropertyAccessor<VarType>
{
public:
	typedef const VarType &(T::*GetterFunction)();
	typedef void (T::*SetterFunction)(VarType);

	WrapperPropertyAccessor(GetterFunction getter, SetterFunction setter) : m_getter(getter), m_setter(setter) {}

	void *Get(void *obj) override {
		if(m_getter) {
			return (void*)&(((T*)obj)->*m_getter)();
		} else {
			return NULL;
		}
	}

	void Set(void *obj, const void *arg) override {
		if(m_setter) {
			(((T*)obj)->*m_setter)(*(VarType*)arg);
		}
	}
	
private:
	GetterFunction m_getter;
	SetterFunction m_setter;
};

} } }
