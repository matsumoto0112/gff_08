#pragma once

#include <strix/net/logging/LogHandler.h>

#include <cstdio>
#include <string>

namespace strix { namespace net { namespace logging {
	
class FileLogHandler : public LogHandler
{
public:
	FileLogHandler();
	FileLogHandler(const std::string &filename);
	virtual ~FileLogHandler();

	const std::string &GetFile() const {
		return m_filename;
	}

	bool Open(const std::string &filename);

	bool IsOpen() const {
		return (m_fp != nullptr);
	}

	void Write(int level, const std::string &message) override;

private:
	FILE *m_fp;
	std::string m_filename;
};

} } }
