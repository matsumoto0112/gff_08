/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

#include "Adapter/StrixNode.h"
#include "Adapter/StrixNodeRoom.h"

#include "StrixNodeRoomInfo.generated.h"

/** Wrapper class for the internal node-node room object pair, used by Strix libraries.
 *  See the definition of stored structures for more information.
 *  Used for room operations that are executed on the node (master) server,
 *  usually meaning establishing a new connection to the specified node (room server) and executing room operations there.
 */
USTRUCT(BlueprintType)
struct FStrixNodeRoomInfo
{
	GENERATED_BODY()

	FStrixNodeRoomInfo() {}
	FStrixNodeRoomInfo(strix::client::match::node::model::CustomizableMatchServerNodePtr node,
		strix::client::match::node::model::CustomizableMatchServerNodeRoomPtr room)
		: Node(node), NodeRoom(room)
	{ }

	/** Structure containing the node information */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoomInfo")
	FStrixNode Node;

	/** Structure containing the node room information */
	UPROPERTY(BlueprintReadOnly, Category = "StrixNodeRoomInfo")
	FStrixNodeRoom NodeRoom;
};