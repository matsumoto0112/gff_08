#pragma once

#include <strix/net/logging/LogFormatter.h>

#include <string>
#include <sstream>

namespace strix { namespace net { namespace logging {

class DefaultLogFormatter : public LogFormatter
{
public:
	DefaultLogFormatter();
	virtual ~DefaultLogFormatter();

	std::string Format(const LogRecord &record) override;
	
	void OutputFileAndLine(const LogRecord &record, std::stringstream &st);
	void OutputDate(const LogRecord &record, std::stringstream &st);
	void OutputLogLevel(const LogRecord &record, std::stringstream &st);
	void OutputLoggerName(const LogRecord &record, std::stringstream &st);
	void OutputThreadId(const LogRecord &record, std::stringstream &st);
	void OutputMessage(const LogRecord &record, std::stringstream &st);
};

} } }
