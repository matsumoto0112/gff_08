// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkData.h"

FStrixPropertyMap UNetworkData::SetStringMemberProperty(const FString propertyName, const FString value) {
	return UStrixBlueprintFunctionLibrary::SetStringProperty(MemberProperties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetIntMemberProperty(const FString propertyName, const int32 value) {
	return UStrixBlueprintFunctionLibrary::SetIntProperty(MemberProperties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetBoolMemberProperty(const FString propertyName, const bool value) {
	return UStrixBlueprintFunctionLibrary::SetBoolProperty(MemberProperties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetStringRoomProperty(const FString propertyName, const FString value) {
	return UStrixBlueprintFunctionLibrary::SetStringProperty(RoomProperties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetIntRoomProperty(const FString propertyName, const int32 value) {
	return UStrixBlueprintFunctionLibrary::SetIntProperty(RoomProperties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetBoolRoomProperty(const FString propertyName, const bool value) {
	return UStrixBlueprintFunctionLibrary::SetBoolProperty(RoomProperties, propertyName, value);
}
