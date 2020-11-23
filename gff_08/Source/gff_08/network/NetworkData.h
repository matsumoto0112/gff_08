// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <Adapter\StrixPropertyMap.h>
#include <StrixBlueprintFunctionLibrary.h>

#include "NetworkData.generated.h"

/**
 *
 */
UCLASS()
class GFF_08_API UNetworkData : public UObject {
	GENERATED_BODY()
public:
	UNetworkData()
		: MasterHostName("4f33be0b0d5a2fdd174aa3d1.game.strixcloud.net")
		, ApplicationID("8df430d4-a8f7-4e53-98ac-1ea2cbdeeabb")
		, HostPort(9122)
		, RoomPort(9123)
		, ChannelID(0)
		, MemberProperties()
		, RoomProperties() {
	}

	UFUNCTION(BlueprintGetter, Category = "NetworkData")
	FString GetMasterHostName() const {
		return MasterHostName;
	}
	UFUNCTION(BlueprintGetter, Category = "NetworkData")
	FString GetApplicationID() const {
		return ApplicationID;
	}
	UFUNCTION(BlueprintGetter, Category = "NetworkData")
	int32 GetHostPort() const {
		return HostPort;
	}
	UFUNCTION(BlueprintGetter, Category = "NetworkData")
	int32 GetRoomPort() const {
		return RoomPort;
	}
	UFUNCTION(BlueprintGetter, Category = "NetworkData")
	int32 GetChannelID() const {
		return ChannelID;
	}
	UFUNCTION(BlueprintSetter, Category = "NetworkData")
	void SetChannelID(int32 id) {
		ChannelID = id;
	}
	UFUNCTION(BlueprintGetter, Category = "NetworkData")
	FStrixPropertyMap GetMemberProperties() const {
		return MemberProperties;
	}
	UFUNCTION(BlueprintGetter, Category = "NetworkData")
	FStrixPropertyMap GetRoomProperties() const {
		return RoomProperties;
	}

	UFUNCTION(BlueprintSetter, Category = "NetworkData")
	void SetMemberProperties(const FStrixPropertyMap properties) {
		MemberProperties = properties;
	}
	UFUNCTION(BlueprintSetter, Category = "NetworkData")
	void SetRoomProperties(const FStrixPropertyMap properties) {
		RoomProperties = properties;
	}

public:
	UFUNCTION(BlueprintPure, Category = "NetworkData")
	FStrixPropertyMap SetStringMemberProperty(const FString propertyName, const FString value);
	UFUNCTION(BlueprintPure, Category = "NetworkData")
	FStrixPropertyMap SetIntMemberProperty(const FString propertyName, const int32 value);
	UFUNCTION(BlueprintPure, Category = "NetworkData")
	FStrixPropertyMap SetBoolMemberProperty(const FString propertyName, const bool value);

	UFUNCTION(BlueprintPure, Category = "NetworkData")
	FStrixPropertyMap SetStringRoomProperty(const FString propertyName, const FString value);
	UFUNCTION(BlueprintPure, Category = "NetworkData")
	FStrixPropertyMap SetIntRoomProperty(const FString propertyName, const int32 value);
	UFUNCTION(BlueprintPure, Category = "NetworkData")
	FStrixPropertyMap SetBoolRoomProperty(const FString propertyName, const bool value);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetMasterHostName, Category = "NetworkData")
	FString MasterHostName;
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetApplicationID, Category = "NetworkData")
	FString ApplicationID;
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetHostPort, Category = "NetworkData")
	int32 HostPort;
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRoomPort, Category = "NetworkData")
	int32 RoomPort;
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetChannelID, BlueprintSetter = SetChannelID, Category = "NetworkData")
	int32 ChannelID;
	UPROPERTY(
		VisibleAnywhere, BlueprintGetter = GetMemberProperties, BlueprintSetter = SetMemberProperties, Category = "NetworkData")
	FStrixPropertyMap MemberProperties;
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRoomProperties, BlueprintSetter = SetRoomProperties, Category = "NetworkData")
	FStrixPropertyMap RoomProperties;
};
