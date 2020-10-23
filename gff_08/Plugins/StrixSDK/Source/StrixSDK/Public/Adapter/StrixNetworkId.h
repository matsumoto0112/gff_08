/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include <string>
#include <sstream>

#include "StrixNetworkId.generated.h"

 /** Wrapper class for the internal network ID object, used by Strix libraries.
  */
USTRUCT(BlueprintType)
struct FStrixNetworkId
{
	GENERATED_BODY()

	FStrixNetworkId() : m_networkObjectId(-1)
	{
		StringId = "-1";
	}
	FStrixNetworkId(int64 id) : m_networkObjectId(id)
	{
		std::stringstream ss;
		ss << id;
		StringId = FString(UTF8_TO_TCHAR(ss.str().c_str()));
	}

	int64 m_networkObjectId;

	UPROPERTY(BlueprintReadOnly, Category = "StrixNetworkId")
	FString StringId;
};