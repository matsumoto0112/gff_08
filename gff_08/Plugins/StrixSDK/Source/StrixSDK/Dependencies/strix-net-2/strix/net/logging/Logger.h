#pragma once

#include <strix/net/logging/LogHandler.h>
#include <strix/net/logging/LogFormatter.h>

#include <map>
#include <memory>
#include <string>
#include <sstream>

namespace strix { namespace net { namespace logging {

class Logger;
typedef std::shared_ptr<Logger> LoggerPtr;

class LogManager
{
public:
	typedef std::map<std::string, LoggerPtr> LoggerMap;

	static LogManager &GetInstance();
	
	LogHandler *GetHandler() const {
		return m_pHandler;
	}

	void SetHandler(LogHandler *pHandler, bool owner = true);

	LogFormatter *GetFormatter() const {
		return m_pFormatter;
	}

	void SetFormatter(LogFormatter *pFormatter, bool owner = true);
	
	LoggerMap &GetLoggerMap() {
		return m_loggerMap;
	}

	void Log(const Logger *pLogger, LogLevel level, const LogRecord &record) {
		Log(pLogger, static_cast<int>(level), record);
	}

	void Log(const Logger *pLogger, int level, const LogRecord &record);

private:
	LogManager();
	~LogManager();

	LoggerMap m_loggerMap;
	LogHandler *m_pHandler;
	bool m_handlerOwner;
	LogFormatter *m_pFormatter;
	bool m_formatterOwner;
};

class Logger
{
public:
	~Logger();

	static const LoggerPtr &GetLogger(const std::string &name);
	
	const std::string &GetName() const {
		return m_name;
	}

	void SetName(const std::string &name) {
		m_name = name;
	}

	LogLevel GetLogLevel() const {
		return m_level;
	}
	
	void SetLogLevel(LogLevel level) {
		m_level = level;
	}

	bool IsLogEnabled(LogLevel level) const {
		return (level >= m_level);
	}
	
	void Log(LogLevel level, const LogRecord &record) {
		LogManager::GetInstance().Log(this, level, record);
	}

	void Log(int level, const LogRecord &record) {
		LogManager::GetInstance().Log(this, level, record);
	}

protected:
	Logger();

	std::string m_name;
	LogLevel m_level;
};


#define STRIX_NET_LOGGER(Name)	static strix::net::logging::LoggerPtr __strix_net_logger() { static strix::net::logging::LoggerPtr pLogger = strix::net::logging::Logger::GetLogger(Name); return pLogger; }

#ifdef _DEBUG

#define _STRIX_NET_LOG_DEBUG_LINE_NUMBER(FILE, LINE)             \
	record.SetFile(FILE);                                        \
	record.SetLine(LINE);                                        \

#else

#define _STRIX_NET_LOG_DEBUG_LINE_NUMBER(FILE, LINE)

#endif

#define STRIX_NET_LOG_(_Logger, Level, Message)              \
	if(_Logger->IsLogEnabled(Level))                         \
	{                                                        \
		std::stringstream _st;                               \
		_st << Message;                                      \
		std::string message = _st.str();                     \
		strix::net::logging::LogRecord record;               \
		_STRIX_NET_LOG_DEBUG_LINE_NUMBER(__FILE__, __LINE__) \
		record.SetLevel(Level);                              \
		record.SetLogger(_Logger);                           \
		record.SetLogMessage(&message);                         \
		_Logger->Log(Level, record);                         \
	}                                                        \

#define STRIX_NET_LOG(_Logger, Level, Message)   STRIX_NET_LOG_(__strix_net_logger(), Level, Message)

#define STRIX_NET_LOG_IS_ENABLED_(_Logger, Level)  _Logger->IsLogEnabled(Level)
#define STRIX_NET_LOG_IS_ENABLED(Level)			   STRIX_NET_LOG_IS_ENABLED_(__strix_net_logger(), Level)

#define STRIX_NET_LOG_TRACE_(_Logger, Message)   STRIX_NET_LOG_(_Logger, strix::net::logging::LogLevel::Trace, Message)
#define STRIX_NET_LOG_DEBUG_(_Logger, Message)   STRIX_NET_LOG_(_Logger, strix::net::logging::LogLevel::Debug, Message)
#define STRIX_NET_LOG_INFO_(_Logger, Message)    STRIX_NET_LOG_(_Logger, strix::net::logging::LogLevel::Info, Message)
#define STRIX_NET_LOG_WARNING_(_Logger, Message) STRIX_NET_LOG_(_Logger, strix::net::logging::LogLevel::Warning, Message)
#define STRIX_NET_LOG_ERROR_(_Logger, Message)   STRIX_NET_LOG_(_Logger, strix::net::logging::LogLevel::Error, Message)
#define STRIX_NET_LOG_FATAL_(_Logger, Message)   STRIX_NET_LOG_(_Logger, strix::net::logging::LogLevel::Fatal, Message)

#define STRIX_NET_LOG_TRACE(Message)   STRIX_NET_LOG_TRACE_(__strix_net_logger(), Message)
#define STRIX_NET_LOG_DEBUG(Message)   STRIX_NET_LOG_DEBUG_(__strix_net_logger(), Message)
#define STRIX_NET_LOG_INFO(Message)    STRIX_NET_LOG_INFO_(__strix_net_logger(), Message)
#define STRIX_NET_LOG_WARNING(Message) STRIX_NET_LOG_WARNING_(__strix_net_logger(), Message)
#define STRIX_NET_LOG_ERROR(Message)   STRIX_NET_LOG_ERROR_(__strix_net_logger(), Message)
#define STRIX_NET_LOG_FATAL(Message)   STRIX_NET_LOG_FATAL_(__strix_net_logger(), Message)


} } }
