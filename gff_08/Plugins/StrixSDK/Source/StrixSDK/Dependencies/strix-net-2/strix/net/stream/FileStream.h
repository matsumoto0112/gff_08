#pragma once

#include <strix/net/stream/Stream.h>

#include <cstdio>

namespace strix { namespace net { namespace stream {

class FileStream : public Stream
{
public:
	FileStream();
	virtual ~FileStream();

	FILE *GetFile();

	void SetFile(FILE *fp);

	size_t GetSize() override;

	size_t Write(const unsigned char *bytes, size_t length) override;

	size_t Read(unsigned char *bytes, size_t length) override;

private:
	FILE *m_fp;
	size_t m_size;
};

} } }
