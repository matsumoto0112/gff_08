#pragma once

#include <strix/net/logging/LogRecord.h>

#include <string>

namespace strix { namespace net { namespace logging {

class LogFormatter
{
public:
	LogFormatter() {}
	virtual ~LogFormatter() {}

	virtual std::string Format(const LogRecord &record) = 0;
};

} } }
