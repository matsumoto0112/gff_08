/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Adapter/StrixPropertyMap.h"

#include <strix/client/match/room/model/CustomizableMatchRoom.h>
#include "StrixRoom.generated.h"

/** Wrapper class for the internal room object, used by Strix libraries.
 *  Room represents room information stored on the room server.
 *  Not to be confused with FStrixNodeRoom, which is the room information stored on the node(master) server.
 */
USTRUCT(BlueprintType)
struct FStrixRoom
{
	GENERATED_BODY()

	FStrixRoom() : Id(0), Capacity(0), MemberCount(0), IsJoinable(true), State(0),
		Key1(0.0), Key2(0.0), Key3(0.0), Key4(0.0), Key5(0.0), Key6(0.0), Key7(0.0), Key8(0.0) {}
	FStrixRoom(strix::client::match::room::model::CustomizableMatchRoomPtr room) :
		Id(0), Capacity(0), MemberCount(0), IsJoinable(true), State(0),
		Key1(0.0), Key2(0.0), Key3(0.0), Key4(0.0), Key5(0.0), Key6(0.0), Key7(0.0), Key8(0.0), m_room(room)
	{
		if (room)
		{
			Id = (int32)room->GetPrimaryKey();
			Capacity = (int32)room->GetCapacity();
			MemberCount = (int32)room->GetMemberCount();
			IsJoinable = room->GetIsJoinable();
			State = (int32)room->GetState();

			if (room->GetName())
				Name = FString(UTF8_TO_TCHAR(room->GetName()->Get().c_str()));

			if (room->GetPassword())
				Password = FString((room->GetPassword()->Get().c_str()));

			Key1 = (float)room->GetKey1();
			Key2 = (float)room->GetKey2();
			Key3 = (float)room->GetKey3();
			Key4 = (float)room->GetKey4();
			Key5 = (float)room->GetKey5();
			Key6 = (float)room->GetKey6();
			Key7 = (float)room->GetKey7();
			Key8 = (float)room->GetKey8();

			StringKey = FString((room->GetStringKey().c_str()));
			Properties = FStrixPropertyMap(room->GetProperties());
		}
	}

	/** Room Id */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	int32 Id;

	/** Capacity of this room.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	int32 Capacity;

	/** Current member count of this room */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	int32 MemberCount;

	/** Whether or not this room is joinable.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	bool IsJoinable;

	/** Id of the current state on the room (not predefined).
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	int32 State;

	/** Name of this room.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	FString Name;

	/** Password of this room.
	 *  Note: not visible if this structure was received from search/get operations.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	FString Password;

	/** Customizable numeric property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	float Key1;

	/** Customizable numeric property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	float Key2;

	/** Customizable numeric property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	float Key3;

	/** Customizable numeric property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	float Key4;

	/** Customizable numeric property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	float Key5;

	/** Customizable numeric property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	float Key6;

	/** Customizable numeric property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	float Key7;

	/** Customizable numeric property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	float Key8;

	/** Customizable string property that can be used for making conditions.
	 *  Note: can be edited on the server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	FString StringKey;

	/** Customizable properties of this room.
	 *  Note: it's not possible to create conditions using those.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixRoom")
	FStrixPropertyMap Properties;

	static const std::set<std::string> KnownNetworkFieldNames;

	strix::client::match::room::model::CustomizableMatchRoomPtr m_room;
};