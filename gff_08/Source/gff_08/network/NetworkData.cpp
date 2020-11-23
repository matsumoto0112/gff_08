// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkData.h"

using StrixUtil = UStrixBlueprintFunctionLibrary;

FStrixPropertyMap UNetworkData::SetStringMemberProperty(
	const FStrixPropertyMap properties, const FString propertyName, const FString value) {
	return StrixUtil::SetStringProperty(properties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetIntMemberProperty(
	const FStrixPropertyMap properties, const FString propertyName, const int32 value) {
	return StrixUtil::SetIntProperty(properties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetBoolMemberProperty(
	const FStrixPropertyMap properties, const FString propertyName, const bool value) {
	return StrixUtil::SetBoolProperty(properties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetStringRoomProperty(
	const FStrixPropertyMap properties, const FString propertyName, const FString value) {
	return StrixUtil::SetStringProperty(properties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetIntRoomProperty(
	const FStrixPropertyMap properties, const FString propertyName, const int32 value) {
	return StrixUtil::SetIntProperty(properties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetBoolRoomProperty(
	const FStrixPropertyMap properties, const FString propertyName, const bool value) {
	return StrixUtil::SetBoolProperty(properties, propertyName, value);
}
