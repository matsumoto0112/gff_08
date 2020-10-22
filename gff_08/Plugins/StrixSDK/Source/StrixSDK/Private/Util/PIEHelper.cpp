/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Util/PIEHelper.h"

#include "Engine/Engine.h"

int32 PIEHelper::GetPIEIdFromGameInstance(UGameInstance* gameInstance)
{
	if (gameInstance)
		return gameInstance->GetWorldContext()->PIEInstance;

	return -1;
}

int32 PIEHelper::GetPIEIdFromWorldContextObject(const UObject* worldContextObject)
{
	if (worldContextObject)
	{
		auto world = worldContextObject->GetWorld();
		if (world)
			return GetPIEIdFromGameInstance(world->GetGameInstance());
	}
	return -1;
}
