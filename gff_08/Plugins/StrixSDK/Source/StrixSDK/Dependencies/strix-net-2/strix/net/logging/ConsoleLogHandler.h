#pragma once

#include <strix/net/logging/LogHandler.h>

#include <string>

namespace strix { namespace net { namespace logging {
	
class ConsoleLogHandler : public LogHandler
{
public:
	ConsoleLogHandler();
	virtual ~ConsoleLogHandler();

	void Write(int level, const std::string &message) override;
};

} } }
