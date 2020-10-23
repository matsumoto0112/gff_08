/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "Engine/GameInstance.h"

/** Class containing various utility functions for managing PIE (Play In Editor)
 *  instances.
 */
class PIEHelper
{
public:
	/** Get the Play In Editor instance Id from the Game Instance object
	 *	@param	gameInstance	Game instance to get the Id from
	 *	@returns	Play In Editor instance Id
	 */
	static int32 GetPIEIdFromGameInstance(UGameInstance* gameInstance);


	/** Get the Play In Editor instance Id from a world context object
	 *	@param	worldContextObject	Object to get the Id from
	 *	@returns	Play In Editor instance Id
	 */
	static int32 GetPIEIdFromWorldContextObject(const UObject* worldContextObject);
};
