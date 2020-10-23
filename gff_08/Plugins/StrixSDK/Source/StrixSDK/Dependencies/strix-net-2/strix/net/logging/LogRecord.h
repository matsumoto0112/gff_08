#pragma once

#include <strix/net/logging/LogLevel.h>

#include <memory>
#include <string>

namespace strix { namespace net { namespace logging {

class Logger;
typedef std::shared_ptr<Logger> LoggerPtr;

class LogRecord
{
public:
	LogRecord() : m_file(NULL), m_line(0), m_message(NULL), m_pLogger(NULL) {}
	~LogRecord() {}

	const char *GetFile() const {
		return m_file;
	}

	void SetFile(const char *file) {
		m_file = file;
	}

	int GetLine() const {
		return m_line;
	}

	void SetLine(int line) {
		m_line = line;
	}

	LogLevel GetLevel() const {
		return m_level;
	}

	void SetLevel(LogLevel level) {
		m_level = level;
	}

	const std::string *GetLogMessage() const {
		return m_message;
	}

	void SetLogMessage(const std::string *message) {
		m_message = message;
	}
	
	const LoggerPtr &GetLogger() const {
		return *m_pLogger;
	}

	void SetLogger(const LoggerPtr &pLogger) {
		m_pLogger = &pLogger;
	}

private:
	const char *m_file;
	int m_line;
	LogLevel m_level;
	const std::string *m_message;
	const LoggerPtr *m_pLogger;
};

} } }
