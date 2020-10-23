/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include <strix/net/object/Object.h>
#include "StrixRelayArg.generated.h"

/** Wrapper class for the internal Strix objects, used in relay (e.g. RPC) messages by Strix libraries.
 */
USTRUCT(BlueprintType)
struct FStrixRelayArg
{
	GENERATED_BODY()

	FStrixRelayArg() : m_objectPtr(nullptr) {}
	FStrixRelayArg(strix::net::object::ObjectPtr objectPtr) : m_objectPtr(objectPtr) {}

	strix::net::object::ObjectPtr m_objectPtr;
};