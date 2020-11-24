// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkData.h"

using StrixUtil = UStrixBlueprintFunctionLibrary;

FStrixPropertyMap UNetworkData::SetStringMemberProperty(const FString propertyName, const FString value) {
	MemberProperties = StrixUtil::SetStringProperty(MemberProperties, propertyName, value);
	return MemberProperties;
}

FStrixPropertyMap UNetworkData::SetIntMemberProperty(const FString propertyName, const int32 value) {
	MemberProperties = StrixUtil::SetIntProperty(MemberProperties, propertyName, value);
	return MemberProperties;
}

FStrixPropertyMap UNetworkData::SetBoolMemberProperty(const FString propertyName, const bool value) {
	MemberProperties = StrixUtil::SetBoolProperty(MemberProperties, propertyName, value);
	return MemberProperties;
}

FStrixPropertyMap UNetworkData::SetStringRoomProperty(const FString propertyName, const FString value) {
	RoomProperties = StrixUtil::SetStringProperty(RoomProperties, propertyName, value);
	return RoomProperties;
}

FStrixPropertyMap UNetworkData::SetIntRoomProperty(const FString propertyName, const int32 value) {
	RoomProperties = StrixUtil::SetIntProperty(RoomProperties, propertyName, value);
	return RoomProperties;
}

FStrixPropertyMap UNetworkData::SetBoolRoomProperty(const FString propertyName, const bool value) {
	RoomProperties = StrixUtil::SetBoolProperty(RoomProperties, propertyName, value);
	return RoomProperties;
}
