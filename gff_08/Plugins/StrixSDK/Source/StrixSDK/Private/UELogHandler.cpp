/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "UELogHandler.h"

#include "CoreMinimal.h"

#include <strix/net/logging/LogLevel.h>

DEFINE_LOG_CATEGORY(LogStrix);

namespace strix { namespace net { namespace logging {

UELogHandler::UELogHandler()
{
}

UELogHandler::~UELogHandler()
{
}

void UELogHandler::Write(int level, const std::string &message)
{
	switch (level)
	{
	case LogLevel::Trace:
		UE_LOG(LogStrix, VeryVerbose, TEXT("%s"), *FString(message.c_str()));
		break;
	case LogLevel::Debug:
		UE_LOG(LogStrix, Verbose, TEXT("%s"), *FString(message.c_str()));
		break;
	case LogLevel::Info:
		UE_LOG(LogStrix, Log, TEXT("%s"), *FString(message.c_str()));
		break;
	case LogLevel::Warning:
		UE_LOG(LogStrix, Warning, TEXT("%s"), *FString(message.c_str()));
		break;
	case LogLevel::Error:
		UE_LOG(LogStrix, Error, TEXT("%s"), *FString(message.c_str()));
		break;
	case LogLevel::Fatal:
		UE_LOG(LogStrix, Fatal, TEXT("%s"), *FString(message.c_str()));
		break;
	default:
		break;
	}
}

} } }
