#pragma once

#include <string>

namespace strix { namespace net { namespace logging {

class LogHandler
{
public:
	LogHandler() {}
	virtual ~LogHandler() {}

	virtual void Write(int level, const std::string &message) = 0;
};

} } }
