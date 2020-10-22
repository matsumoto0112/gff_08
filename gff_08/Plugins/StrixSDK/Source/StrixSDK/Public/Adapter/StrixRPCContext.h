/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "Adapter/StrixRoomMember.h"

#include "StrixRPCContext.generated.h"

/** Wrapper class for the RPC context object.
  */
USTRUCT(BlueprintType)
struct FStrixRpcContext
{
	GENERATED_BODY()

	FStrixRpcContext() = default;
	FStrixRpcContext(int32 id, int32 roomId) : SenderMemberId(id), RoomId(roomId) {}

	UPROPERTY(BlueprintReadOnly, Category = "StrixRPCContext")
	int32 SenderMemberId;

	UPROPERTY(BlueprintReadOnly, Category = "StrixRPCContext")
	int32 RoomId;

};
