/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

#include <strix/net/logging/LogHandler.h>

DECLARE_LOG_CATEGORY_EXTERN(LogStrix, Log, All);

namespace strix { namespace net { namespace logging {

/** Unreal Engine implementation of the Strix Log Handler.
 *  Provides the bridge between Strix and UE Editor logs.
 */
class UELogHandler : public LogHandler
{
public:
	UELogHandler();
	virtual ~UELogHandler();

	/** Write the message to the log
	 *  @param	level	Level (severity) of the message
	 *  @param	message	The message to write
	 */
	virtual void Write(int level, const std::string &message);
};

} } }
