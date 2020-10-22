/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Sync/UESyncProperties.h"

#include "Sync/UENotifiableSyncGroup.h"

using namespace strix::client::ingame::sync;


void UESyncPropertyUtils::SyncUEProperty(UProperty* prop, UObject* object, const strix::client::ingame::sync::SyncGroupPtr& sync)
{
	SyncUEProperty(prop, object, sync, std::string(TCHAR_TO_UTF8(*object->GetClass()->GetName())));
}

void UESyncPropertyUtils::SyncUEProperty(UProperty* prop, UObject* object, const SyncGroupPtr &sync, FName notifyFunctionName, UObject* notifyFunctionOwner)
{
	SyncUEProperty(prop, object, sync, std::string(TCHAR_TO_UTF8(*object->GetClass()->GetName())), notifyFunctionName, notifyFunctionOwner);
}

void UESyncPropertyUtils::SyncUEProperty(UProperty* prop, void* object, const strix::client::ingame::sync::SyncGroupPtr& sync, const std::string& topLevelName)
{
	SyncPropertyPtr syncProperty = Sync(prop, object, sync, topLevelName);
	if (!syncProperty)
	{
		if (auto structProperty = Cast<UStructProperty>(prop))
		{
			TraverseAndSyncStruct(structProperty, object, sync, topLevelName);
		}
	}
	else
	{
		sync->AddProperty(syncProperty);
	}
}

void UESyncPropertyUtils::SyncUEProperty(UProperty* prop, void* object, const SyncGroupPtr &sync, const std::string &topLevelName, FName notifyFunctionName, UObject* notifyFunctionOwner)
{
	SyncPropertyPtr syncProperty = Sync(prop, object, sync, topLevelName);
	if(!syncProperty)
	{
		if(auto structProperty = Cast<UStructProperty>(prop))
		{
			TraverseAndSyncStruct(structProperty, object, sync, topLevelName, notifyFunctionName, notifyFunctionOwner);
		}
	}
	else
	{
		sync->AddProperty(syncProperty);
	}
	if(notifyFunctionOwner && syncProperty)
	{
		UENotifiableSyncGroupPtr syncGroup = std::static_pointer_cast<UENotifiableSyncGroup>(sync);
		syncGroup->AddNotifyFunction(notifyFunctionOwner->FindFunction(notifyFunctionName), notifyFunctionOwner, syncProperty);
	}
}

void UESyncPropertyUtils::TraverseAndSyncStruct(UStructProperty* structProperty, void* object, const strix::client::ingame::sync::SyncGroupPtr& sync, const std::string& topLevelName)
{
	for (TFieldIterator<UProperty> it(structProperty->Struct); it; ++it)
	{
		SyncUEProperty(
			*it,
			structProperty->ContainerPtrToValuePtr<void>(object),
			sync,
			topLevelName + "." + std::string(TCHAR_TO_UTF8(*structProperty->GetNameCPP()))
		);
	}
}

void UESyncPropertyUtils::TraverseAndSyncStruct(UStructProperty* structProperty, void* object, const SyncGroupPtr &sync, const std::string &topLevelName, FName notifyFunctionName, UObject* notifyFunctionOwner)
{	
	for (TFieldIterator<UProperty> it(structProperty->Struct); it; ++it)
	{
		SyncUEProperty(
			*it,
			structProperty->ContainerPtrToValuePtr<void>(object),
			sync,
			topLevelName + "." + std::string(TCHAR_TO_UTF8(*structProperty->GetNameCPP())),
			notifyFunctionName,
			notifyFunctionOwner
		);
	}
}

SyncPropertyPtr UESyncPropertyUtils::Sync(UProperty* prop, void* object, const strix::client::ingame::sync::SyncGroupPtr& sync, const std::string& topLevelName)
{
	const auto name = topLevelName + "." + TCHAR_TO_UTF8(*prop->GetNameCPP());
	SyncPropertyPtr syncProperty;
	if (const auto intProperty = Cast<UIntProperty>(prop))
	{
		syncProperty = GetUENumProperty<int32>(intProperty, object, name);
	}
	else if (const auto boolProperty = Cast<UBoolProperty>(prop))
	{
		syncProperty = GetUESyncProperty(boolProperty, object, name);
	}
	else if (const auto int64Property = Cast<UInt64Property>(prop))
	{
		syncProperty = GetUENumProperty<int64>(int64Property, object, name);
	}
	else if (const auto int16Property = Cast<UInt16Property>(prop))
	{
		syncProperty = GetUENumProperty<int16>(int16Property, object, name);
	}
	else if (const auto int8Property = Cast<UInt8Property>(prop))
	{
		syncProperty = GetUENumProperty<int8>(int8Property, object, name);
	}
	else if (const auto uint64Property = Cast<UUInt64Property>(prop))
	{
		syncProperty = GetUENumProperty<uint64>(uint64Property, object, name);
	}
	else if (const auto uint32Property = Cast<UUInt32Property>(prop))
	{
		syncProperty = GetUENumProperty<uint32>(uint32Property, object, name);
	}
	else if (const auto uint16Property = Cast<UUInt16Property>(prop))
	{
		syncProperty = GetUENumProperty<uint16>(uint16Property, object, name);
	}
	else if (const auto byteProperty = Cast<UByteProperty>(prop))
	{
		syncProperty = GetUESyncProperty(byteProperty, object, name);
	}
	else if (const auto floatProperty = Cast<UFloatProperty>(prop))
	{
		syncProperty = GetUENumProperty<float>(floatProperty, object, name);
	}
	else if (const auto doubleProperty = Cast<UDoubleProperty>(prop))
	{
		syncProperty = GetUENumProperty<double>(doubleProperty, object, name);
	}
	else if (const auto enumProperty = Cast<UEnumProperty>(prop))
	{
		syncProperty = GetUESyncProperty(enumProperty, object, name);
	}
	else if (const auto strProperty = Cast<UStrProperty>(prop))
	{
		syncProperty = GetUESyncProperty(strProperty, object, name);
	}
	else if (const auto nameProperty = Cast<UNameProperty>(prop))
	{
		syncProperty = GetUESyncProperty(nameProperty, object, name);
	}
	else if (const auto textProperty = Cast<UTextProperty>(prop))
	{
		syncProperty = GetUESyncProperty(textProperty, object, name);
	}
	else if (const auto arrayProperty = Cast<UArrayProperty>(prop))
	{
		syncProperty = GetUESyncProperty(arrayProperty, object, name);
	}
	return syncProperty;
}

SyncPropertyPtr UESyncPropertyUtils::GetUESyncProperty(UBoolProperty* boolProperty, void* object, const std::string &name)
{
	const auto target = boolProperty->ContainerPtrToValuePtr<bool>(object);
	return std::make_shared<UEFunctionalSyncProperty<bool>>(
		std::bind(&UBoolProperty::GetPropertyValue, boolProperty, target),
		std::bind(&UBoolProperty::SetPropertyValue, boolProperty, target, std::placeholders::_1),
		name);
}

SyncPropertyPtr UESyncPropertyUtils::GetUESyncProperty(UByteProperty* byteProperty, void* object, const std::string &name)
{
	return std::make_shared<UEFunctionalSyncProperty<char>>(
		[=]()
			{
				return *byteProperty->ContainerPtrToValuePtr<char>(object);
			},
			[=](char value)
			{
				*byteProperty->ContainerPtrToValuePtr<char>(object) = value;
			}, 
		name);
}

SyncPropertyPtr UESyncPropertyUtils::GetUESyncProperty(UEnumProperty* enumProperty, void* object, const std::string &name)
{
	const auto target = enumProperty->ContainerPtrToValuePtr<void>(object);
	return std::make_shared<UEFunctionalSyncProperty<long long>>(
		[=]()
			{
				return static_cast<long long>(enumProperty->GetUnderlyingProperty()->GetSignedIntPropertyValue(target));
			},
			[=](long long value)
			{
				enumProperty->GetUnderlyingProperty()->SetIntPropertyValue(target, static_cast<int64>(value));
			},
		name);
}

SyncPropertyPtr UESyncPropertyUtils::GetUESyncProperty(UStrProperty* strProperty, void* object, const std::string &name)
{
	const auto target = strProperty->GetPropertyValuePtr_InContainer(object);
	return std::make_shared<UEFunctionalSyncProperty<std::string>>(
		[=]()
			{
				FString s = *target;
				return std::string(TCHAR_TO_UTF8(*s));
			},
			[=](std::string value)
			{
				*target = FString(UTF8_TO_TCHAR(value.c_str()));
			},
		name);
}

SyncPropertyPtr UESyncPropertyUtils::GetUESyncProperty(UTextProperty* textProperty, void* object, const std::string &name)
{
	const auto target = textProperty->GetPropertyValuePtr_InContainer(object);
	return std::make_shared<UEFunctionalSyncProperty<std::string>>(
		[=]()
		{
			FText s = *target;
			return std::string(TCHAR_TO_UTF8(*s.ToString()));
		},
			[=](std::string value) {
			*target = FText::FromString(FString(value.c_str()));
		},
		name);
}

SyncPropertyPtr UESyncPropertyUtils::GetUESyncProperty(UNameProperty* nameProperty, void* object, const std::string &name)
{
	const auto target = nameProperty->GetPropertyValuePtr_InContainer(object);
	return std::make_shared<UEFunctionalSyncProperty<std::string>>(
		[=]()
			{
				FName s = *target;
				return std::string(TCHAR_TO_UTF8(*s.ToString()));
			},
			[=](std::string value)
			{
				*target = FName(value.c_str());
			},
		name);
}

SyncPropertyPtr UESyncPropertyUtils::GetUESyncProperty(UArrayProperty* arrayProperty, void* object, const std::string &name)
{
#if ENGINE_MINOR_VERSION >= 25
	FFieldClass* innerClass = arrayProperty->Inner->GetClass();
#else
	UClass* innerClass = arrayProperty->Inner->GetClass();
#endif

	if(innerClass->IsChildOf(UInt8Property::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<int8>>(object);
		return std::make_shared<UEArraySyncProperty<int8>>(name, *target);
	}
	if (innerClass->IsChildOf(UInt16Property::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<int16>>(object);
		return std::make_shared<UEArraySyncProperty<int16>>(name, *target);
	}
	if (innerClass->IsChildOf(UIntProperty::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<int32>>(object);
		return std::make_shared<UEArraySyncProperty<int32>>(name, *target);
	}
	if (innerClass->IsChildOf(UInt64Property::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<int64>>(object);
		return std::make_shared<UEArraySyncProperty<int64>>(name, *target);
	}
	if (innerClass->IsChildOf(UByteProperty::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<uint8>>(object);
		return std::make_shared<UEArraySyncProperty<uint8>>(name, *target);
	}
	if (innerClass->IsChildOf(UUInt16Property::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<uint16>>(object);
		return std::make_shared<UEArraySyncProperty<uint16>>(name, *target);
	}
	if (innerClass->IsChildOf(UUInt32Property::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<uint32>>(object);
		return std::make_shared<UEArraySyncProperty<uint32>>(name, *target);
	}
	if (innerClass->IsChildOf(UUInt64Property::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<uint64>>(object);
		return std::make_shared<UEArraySyncProperty<uint64>>(name, *target);
	}
	if (innerClass->IsChildOf(UFloatProperty::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<float>>(object);
		return std::make_shared<UEArraySyncProperty<float>>(name, *target);
	}
	if (innerClass->IsChildOf(UDoubleProperty::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<double>>(object);
		return std::make_shared<UEArraySyncProperty<double>>(name, *target);
	}
	if (innerClass->IsChildOf(UBoolProperty::StaticClass()))
	{
		auto target = arrayProperty->ContainerPtrToValuePtr<TArray<bool>>(object);
		return std::make_shared<UEArraySyncProperty<bool>>(name, *target);
	}
	return nullptr;
}
