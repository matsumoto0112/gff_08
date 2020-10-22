#pragma once

namespace strix { namespace net { namespace stream {

class Stream
{
public:
	Stream();
	virtual ~Stream();

	virtual size_t GetSize() = 0;

	virtual size_t Write(const unsigned char *bytes, size_t length) = 0;

	virtual size_t Read(unsigned char *bytes, size_t length) = 0;
};

} } }
