/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Adapter/StrixPropertyMap.h"

#include <strix/client/match/node/model/CustomizableMatchServerNodeRoom.h>
#include "StrixNodeRoom.generated.h"

/** Wrapper class for the internal node room object, used by Strix libraries.
 *  Node room represents room information stored on the node (master) server.
 *  Not to be confused with FStrixRoom, which is the room information stored on the room server.
 */
USTRUCT(BlueprintType)
struct FStrixNodeRoom
{
	GENERATED_BODY()

	FStrixNodeRoom() : Id(0), RoomId(0), Capacity(0), MemberCount(0), IsPasswordProtected(false), IsJoinable(true), State(0),
		Key1(0.0), Key2(0.0), Key3(0.0), Key4(0.0), Key5(0.0), Key6(0.0), Key7(0.0), Key8(0.0) {}
	FStrixNodeRoom(strix::client::match::node::model::CustomizableMatchServerNodeRoomPtr nodeRoom) :
		Id(0), RoomId(0), Capacity(0), MemberCount(0), IsPasswordProtected(false), IsJoinable(true), State(0),
		Key1(0.0), Key2(0.0), Key3(0.0), Key4(0.0), Key5(0.0), Key6(0.0), Key7(0.0), Key8(0.0), m_nodeRoom(nodeRoom)
	{
		if (nodeRoom)
		{
			Id = (int32)nodeRoom->GetPrimaryKey();
			RoomId = (int32)nodeRoom->GetRoomId();
			Capacity = (int32)nodeRoom->GetCapacity();
			MemberCount = (int32)nodeRoom->GetMemberCount();
			IsPasswordProtected = nodeRoom->GetIsPasswordProtected();
			IsJoinable = nodeRoom->GetIsJoinable();
			State = (int32)nodeRoom->GetState();

			if (nodeRoom->GetName())
				Name = FString(UTF8_TO_TCHAR(nodeRoom->GetName()->Get().c_str()));

			Key1 = (float)nodeRoom->GetKey1();
			Key2 = (float)nodeRoom->GetKey2();
			Key3 = (float)nodeRoom->GetKey3();
			Key4 = (float)nodeRoom->GetKey4();
			Key5 = (float)nodeRoom->GetKey5();
			Key6 = (float)nodeRoom->GetKey6();
			Key7 = (float)nodeRoom->GetKey7();
			Key8 = (float)nodeRoom->GetKey8();

			StringKey = FString(UTF8_TO_TCHAR(nodeRoom->GetStringKey().c_str()));
			Properties = FStrixPropertyMap(nodeRoom->GetProperties());
		}
	}

	/** Id
	 *  Note: different than room id. This is the unique identifier of the node id - room id pair stored on the node (master) server.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	int32 Id;

	/** Room Id */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	int32 RoomId;

	/** Capacity of this room */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	int32 Capacity;

	/** Current member count of this room */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	int32 MemberCount;

	/** Whether or not this room is password protected */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	bool IsPasswordProtected;

	/** Whether or not this room is joinable */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	bool IsJoinable;

	/** Id of the current state on the room (not predefined) */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	int32 State;

	/** Name of this room */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	FString Name;

	/** Customizable numeric property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	float Key1;

	/** Customizable numeric property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	float Key2;

	/** Customizable numeric property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	float Key3;

	/** Customizable numeric property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	float Key4;

	/** Customizable numeric property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	float Key5;

	/** Customizable numeric property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	float Key6;

	/** Customizable numeric property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	float Key7;

	/** Customizable numeric property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	float Key8;

	/** Customizable string property that can be used for making conditions */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	FString StringKey;

	/** Customizable properties of this room.
	 *  Note: it's not possible to create conditions using those.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoom")
	FStrixPropertyMap Properties;

	strix::client::match::node::model::CustomizableMatchServerNodeRoomPtr m_nodeRoom;
};