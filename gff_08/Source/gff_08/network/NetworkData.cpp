// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkData.h"

FStrixPropertyMap UNetworkData::SetStringProperty(const FString propertyName, const FString value) {
	return UStrixBlueprintFunctionLibrary::SetStringProperty(MemberProperties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetIntProperty(const FString propertyName, const int32 value) {
	return UStrixBlueprintFunctionLibrary::SetIntProperty(MemberProperties, propertyName, value);
}

FStrixPropertyMap UNetworkData::SetBoolProperty(const FString propertyName, const bool value) {
	return UStrixBlueprintFunctionLibrary::SetBoolProperty(MemberProperties, propertyName, value);
}
