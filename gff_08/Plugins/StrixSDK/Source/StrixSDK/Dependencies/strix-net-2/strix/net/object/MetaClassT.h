#pragma once

#include <strix/net/object/_MetaClassT.h>
#include <strix/net/object/PropertyAccessor.h>

#include <string>

namespace strix { namespace net { namespace object {

template <class T>
template <typename ArgType>
void MetaClassBaseT<T>::AddProperty(const std::string &name, const ArgType *offset) {
	MetaClass::AddPropertyAccessor(
		name, 
		MetaClassT<ArgType>::Get(),
		PropertyAccessorPtr(new DefaultPropertyAccessor<ArgType>(static_cast<uint32_t>(reinterpret_cast<size_t>(offset))))
	);
}

template <class T>
template <typename VarType, typename GetterFuncType, typename SetterFuncType>
void MetaClassBaseT<T>::AddAccessorProperty(const std::string &name, GetterFuncType getterFunction, SetterFuncType setterFunction) {
	MetaClass::AddPropertyAccessor(
		name,
		MetaClassT<VarType>::Get(),
		PropertyAccessorPtr(new WrapperPropertyAccessor<T, VarType>(getterFunction, setterFunction))
	);
}

template <class T>
template <typename VarType, typename ArgType>
void MetaClassBaseT<T>::AddTypedProperty(const std::string &name, const ArgType *offset) {
	MetaClass::AddPropertyAccessor(
		name,
		MetaClassT<VarType>::Get(),
		PropertyAccessorPtr(new TypedPropertyAccessor<VarType, ArgType>(static_cast<uint32_t>(reinterpret_cast<size_t>(offset))))
	);
}

} } }