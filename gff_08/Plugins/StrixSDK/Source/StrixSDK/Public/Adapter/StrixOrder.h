/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

#include <strix/client/core/model/manager/filter/Order.h>
#include "StrixOrder.generated.h"

/** Wrapper class for the internal order object, used by Strix libraries.
 */
USTRUCT(BlueprintType)
struct FStrixOrder
{
	GENERATED_BODY()

	FStrixOrder() : m_order(nullptr) {}
	FStrixOrder(strix::client::core::model::manager::filter::OrderPtr order) : m_order(order) {}

	strix::client::core::model::manager::filter::OrderPtr m_order;
};
