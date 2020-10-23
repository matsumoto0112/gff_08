#pragma once

#include <strix/net/stream/Stream.h>

namespace strix { namespace net { namespace buffer {
    class Buffer;
} } }

namespace strix { namespace net { namespace stream {

class BufferStream : public Stream
{
public:
	BufferStream();
	virtual ~BufferStream();

	buffer::Buffer *GetBuffer();

	void SetBuffer(buffer::Buffer *pBuffer);

	size_t GetSize() override;

	size_t Write(const unsigned char *bytes, size_t length) override;

	size_t Read(unsigned char *bytes, size_t length) override;

private:
	buffer::Buffer *m_buf;
};

} } }
