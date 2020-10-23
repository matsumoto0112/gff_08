/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

#include <strix/client/core/model/manager/filter/Condition.h>
#include "StrixCondition.generated.h"

/** Wrapper class for the internal condition object, used by Strix libraries.
 */
USTRUCT(BlueprintType)
struct FStrixCondition
{
	GENERATED_BODY()

	FStrixCondition() : m_condition(nullptr) {}
	FStrixCondition(strix::client::core::model::manager::filter::ConditionPtr condition) : m_condition(condition) {}

	strix::client::core::model::manager::filter::ConditionPtr m_condition;
};
