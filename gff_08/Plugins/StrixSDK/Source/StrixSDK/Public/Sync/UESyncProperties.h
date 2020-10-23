/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Util/StrixUtil.h"

#include <strix/client/ingame/sync/SyncPropertyT.h>
#include <strix/client/ingame/sync/SyncProperty.h>
#include <strix/client/ingame/sync/SyncGroup.h>

#include <functional>

/**
 *  SyncProperty implementation that uses stored function to get/set values.
 */
template <typename T>
class UEFunctionalSyncProperty : public strix::client::ingame::sync::SyncPropertyT<T>
{
public:
	UEFunctionalSyncProperty(std::function<T()> get, std::function<void(T)> set, std::string prop)
		: m_setter(std::move(set)), m_getter(std::move(get)), m_name(std::move(prop))
	{
		m_value = m_getter();
	}

	strix::net::object::ObjectPtr GetObjectValue() override
	{
		m_value = m_getter();
		return strix::net::object::ObjectAdapter(GetValue());
	}

	void SetObjectValue(strix::net::object::ObjectPtr objectValue) override
	{
		T out;
		if (strix::client::core::util::ObjectConverter::TryConvertObjectToValue<T>(objectValue, out))
		{
			SetValue(out);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to convert: %s"), *FString(m_name.c_str()));
		}
	}

	int GetPropertyId() const override
	{
		return StrixUtil::GetHashValue(m_name);
	}

	const std::string &GetPropertyName() const override
	{
		return m_name;
	}

	const T &GetValue() const override
	{
		return m_value;
	}
	void SetValue(T val) override
	{
		m_value = val;
		m_setter(m_value);
	}

private:
	std::function<void(T)> m_setter;
	std::function<T()> m_getter;
	T m_value;
	std::string m_name;
};

/**
 *  Template SyncProperty implementation for use with Unreal Engine.
 */
template <typename T>
class UESyncProperty : public strix::client::ingame::sync::SyncPropertyT<T>
{
public:
	UESyncProperty(std::string prop, T& val)
		: m_value(val), m_name(std::move(prop))
	{
	}

	strix::net::object::ObjectPtr GetObjectValue() override
	{
		return strix::net::object::ObjectAdapter(GetValue());
	}

	void SetObjectValue(strix::net::object::ObjectPtr objectValue) override
	{
		T out;
		if (strix::client::core::util::ObjectConverter::TryConvertObjectToValue<T>(objectValue, out))
		{
			SetValue(out);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to convert: %s"), m_name.c_str());
		}
	}

	const std::string &GetPropertyName() const override
	{
		return m_name;
	}

	int GetPropertyId() const override
	{
		return StrixUtil::GetHashValue(m_name);
	}

	const T &GetValue() const override
	{
		return m_value;
	}

	void SetValue(T val) override
	{
		m_value = std::move(val);
	}

private:
	T& m_value;
	std::string m_name;
};

/**
 *  Template SyncProperty implementation for use with Unreal Engine containers.
 */
template <typename T>
class UEArraySyncProperty : public strix::client::ingame::sync::SyncProperty
{
public:
	UEArraySyncProperty(std::string prop, TArray<T> &cont)
		: m_container(cont), m_name(std::move(prop))
	{
		m_objectVector = std::make_shared<strix::net::object::ObjectVector>();
	}

	strix::net::object::ObjectPtr GetObjectValue() override
	{
		m_objectVector->Get().resize(m_container.Num());
		for(int i = 0; i < m_container.Num(); i++)
		{
			m_objectVector->Get()[i] = strix::net::object::ObjectAdapter(m_container[i]);
		}
		return m_objectVector;
	}

	void SetObjectValue(strix::net::object::ObjectPtr objectValue) override
	{
		if (objectValue->InstanceOf<strix::net::object::ObjectVector>())
		{
			auto vec = std::static_pointer_cast<strix::net::object::ObjectVector>(objectValue);
			m_container.SetNumUninitialized(vec->Get().size());
			for (int i = 0; i < vec->Get().size(); i++)
			{
				if (!strix::client::core::util::ObjectConverter::TryConvertObjectToValue<T>(vec->Get()[i], m_container[i]))
				{
					UE_LOG(LogTemp, Fatal, TEXT("Failed to convert value at index %i in: %s"), i, m_name.c_str());
				}
			}
		}
	}

	const std::string &GetPropertyName() const override
	{
		return m_name;
	}

	int GetPropertyId() const override
	{
		return StrixUtil::GetHashValue(m_name);
	}

private:
	TArray<T> &m_container;
	std::string m_name;
	std::shared_ptr<strix::net::object::ObjectVector> m_objectVector;
};

/**
 *  Class containing helper functions for creating sync properties.
 */
class UESyncPropertyUtils
{
public:

	/**
	 *  Create a SyncProperty object using specified Unreal property (UProperty).
	 *  @param	boolProperty	Property to bind
	 *  @param	object	Object to get the property value from
	 *  @param	name	Property name
	 *  @returns	Created SyncProperty object
	 */
	static strix::client::ingame::sync::SyncPropertyPtr GetUESyncProperty(UBoolProperty* boolProperty, void* object, const std::string &name);

	/**
	 *  Create a SyncProperty object using specified Unreal property (UProperty).
	 *  @param	enumProperty	Property to bind
	 *  @param	object	Object to get the property value from
	 *  @param	name	Property name
	 *  @returns	Created SyncProperty object
	 */
	static strix::client::ingame::sync::SyncPropertyPtr GetUESyncProperty(UEnumProperty* enumProperty, void* object, const std::string &name);

	/**
	 *  Create a SyncProperty object using specified Unreal property (UProperty).
	 *  @param	strProperty	Property to bind
	 *  @param	object	Object to get the property value from
	 *  @param	name	Property name
	 *  @returns	Created SyncProperty object
	 */
	static strix::client::ingame::sync::SyncPropertyPtr GetUESyncProperty(UStrProperty* strProperty, void* object, const std::string &name);

	/**
	 *  Create a SyncProperty object using specified Unreal property (UProperty).
	 *  @param	textProperty	Property to bind
	 *  @param	object	Object to get the property value from
	 *  @param	name	Property name
	 *  @returns	Created SyncProperty object
	 */
	static strix::client::ingame::sync::SyncPropertyPtr GetUESyncProperty(UTextProperty* textProperty, void* object, const std::string &name);

	/**
	 *  Create a SyncProperty object using specified Unreal property (UProperty).
	 *  @param	nameProperty	Property to bind
	 *  @param	object	Object to get the property value from
	 *  @param	name	Property name
	 *  @returns	Created SyncProperty object
	 */
	static strix::client::ingame::sync::SyncPropertyPtr GetUESyncProperty(UNameProperty* nameProperty, void* object, const std::string &name);

	/**
	 *  Create a SyncProperty object using specified Unreal property (UProperty).
	 *  @param	arrayProperty	Property to bind
	 *  @param	object	Object to get the property value from
	 *  @param	name	Property name
	 *  @returns	Created SyncProperty object
	 */
	static strix::client::ingame::sync::SyncPropertyPtr GetUESyncProperty(UArrayProperty* arrayProperty, void* object, const std::string& name);

	/**
	 *  Create a SyncProperty object using specified Unreal property (UProperty).
	 *  @param	byteProperty	Property to bind
	 *  @param	object	Object to get the property value from
	 *  @param	name	Property name
	 *  @returns	Created SyncProperty object
	 */
	static strix::client::ingame::sync::SyncPropertyPtr GetUESyncProperty(UByteProperty* byteProperty, void* object, const std::string &name);

	/**
	 *  Create a SyncProperty object using specified Unreal numeric property (TProperty_Numeric).
	 *  @param	prop	Property to bind
	 *  @param	object	Object to get the property value from
	 *  @param	name	Property name
	 *  @returns	Created SyncProperty object
	 */
	template <typename T>
	static strix::client::ingame::sync::SyncPropertyPtr GetUENumProperty(TProperty_Numeric<T>* prop, void* object, const std::string name)
	{
		return std::make_shared<UEFunctionalSyncProperty<T>>(
			[=]()
			{
				return *prop->template ContainerPtrToValuePtr<T>(object);
			},
			[=](T value)
			{
				*prop->template ContainerPtrToValuePtr<T>(object) = value;
			}, name);
	}

	/**
	 *  Create a SyncProperty object and register it on the provided Sync Group.
	 *  @param	prop	Property to sync
	 *  @param	object	Object to get the property value from
	 *  @param	sync	Sync group to register the property on
	 */
	static void SyncUEProperty(UProperty* prop, UObject* object, const strix::client::ingame::sync::SyncGroupPtr &sync);

	/**
	 *  Create a SyncProperty object and register it on the provided Sync Group.
	 *  @param	prop	Property to sync
	 *  @param	object	Object to get the property value from
	 *  @param	sync	Sync group to register the property on
	 *  @param	notifyFunctionName	Name of the notification function called when this property is updated
	 *  @param	notifyFunctionOwner	Object to execute the notification function on
	 */
	static void SyncUEProperty(UProperty* prop, UObject* object, const strix::client::ingame::sync::SyncGroupPtr &sync, FName notifyFunctionName, UObject* notifyFunctionOwner);

private:
	/**
	 *  Create a SyncProperty object and register it on the provided Sync Group.
	 *  @param	prop	Property to sync
	 *  @param	object	Object to get the property value from
	 *  @param	sync	Sync group to register the property on
	 *  @param	topLevelName	Prefix that will be used to create the property name
	 */
	static strix::client::ingame::sync::SyncPropertyPtr Sync(UProperty* prop, void* object, const strix::client::ingame::sync::SyncGroupPtr &sync, const std::string &topLevelName);

	/**
	 *  Create a SyncProperty object and register it on the provided Sync Group.
	 *  @param	prop	Property to sync
	 *  @param	object	Object to get the property value from
	 *  @param	sync	Sync group to register the property on
	 *  @param	topLevelName	Prefix that will be used to create the property name
	 */
	static void SyncUEProperty(UProperty* prop, void* object, const strix::client::ingame::sync::SyncGroupPtr &sync, const std::string &topLevelName);

	/**
	 *  Create a SyncProperty object and register it on the provided Sync Group.
	 *  @param	prop	Property to sync
	 *  @param	object	Object to get the property value from
	 *  @param	sync	Sync group to register the property on
	 *  @param	topLevelName	Prefix that will be used to create the property name
	 *  @param	notifyFunctionName	Name of the notification function called when this property is updated
	 *  @param	notifyFunctionOwner	Object to execute the notification function on
	 */
	static void SyncUEProperty(UProperty* prop, void* object, const strix::client::ingame::sync::SyncGroupPtr &sync, const std::string &topLevelName, FName notifyFunctionName, UObject* notifyFunctionOwner);

	/**
	 *  Traverse structure properties and create sync properties from them.
	 *  @param	structProperty	Property to sync
	 *  @param	object	Object to get the property value from
	 *  @param	sync	Sync group to register the property on
	 *  @param	topLevelName	Prefix that will be used to create the property name
	 */
	static void TraverseAndSyncStruct(UStructProperty* structProperty, void* object, const strix::client::ingame::sync::SyncGroupPtr &sync, const std::string &topLevelName);

	/**
	 *  Traverse structure properties and create sync properties from them.
	 *  @param	structProperty	Property to sync
	 *  @param	object	Object to get the property value from
	 *  @param	sync	Sync group to register the property on
	 *  @param	topLevelName	Prefix that will be used to create the property name
	 *  @param	notifyFunctionName	Name of the notification function called when this property is updated
	 *  @param	notifyFunctionOwner	Object to execute the notification function on
	 */
	static void TraverseAndSyncStruct(UStructProperty* structProperty, void* object, const strix::client::ingame::sync::SyncGroupPtr &sync, const std::string &topLevelName, FName notifyFunctionName, UObject* notifyFunctionOwner);
};