/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

#include <strix/client/core/error/ErrorCategory.h>

#include "StrixErrors.generated.h"

UENUM(BlueprintType)
enum class EStrixErrorCategory : uint8
{
	StrixNet = 0 UMETA(DisplayName = "StrixNet"),
	StrixClient = strix::client::core::error::ErrorCategory::StrixClient UMETA(DisplayName = "StrixClient"),
	External = strix::client::core::error::ErrorCategory::External UMETA(DisplayName = "External"),
	StrixUESDK UMETA(DisplayName = "StrixUESDK"),
};

static_assert(strix::client::core::error::ErrorCategory::StrixNet == 0,
	"strix::client::core::error::ErrorCategory::StrixNet must be 0 or EStrixErrorCategory should have an entry which equals to 0");

enum StrixUESDKErrorCode : int {
	// MS (1-100)
	MasterServerAlreadyConnected = 1,
	MasterServerNotConnected = 2,

	// RS(101-200)
	RoomServerAlreadyConnected = 101,
	RoomServerNotConnected = 102,

	// RC(201-300)
	RoomContextAlreadyExists = 201,
	RoomContextDoesNotExist = 202,
};

class StrixErrorCodeConverter
{
public:
	static EStrixErrorCategory ConvertStrixErrorCategoryToUEEnum(strix::client::core::error::ErrorCategory errorCategory)
	{
		switch (errorCategory)
		{
		case strix::client::core::error::ErrorCategory::StrixNet:
			return EStrixErrorCategory::StrixNet;
		case strix::client::core::error::ErrorCategory::StrixClient:
			return EStrixErrorCategory::StrixClient;
		default:
			return EStrixErrorCategory::External;
		}
	}
};