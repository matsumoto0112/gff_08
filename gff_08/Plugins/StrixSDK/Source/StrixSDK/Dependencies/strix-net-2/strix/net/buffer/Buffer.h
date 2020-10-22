#pragma once

#include <vector>

namespace strix { namespace net { namespace buffer {

struct RawBuffer
{
	uint8_t *buf;
	size_t size;
};

class Buffer
{
public:
	Buffer(void) {}
	virtual ~Buffer(void) {}
	
	virtual void Init(size_t size) = 0;

	virtual bool Ensure(size_t size) = 0;

	virtual size_t GetReadableSize() const = 0;

	virtual size_t GetWritableSize() const = 0;

	virtual size_t Read(uint8_t *buf, size_t length) = 0;
	
	virtual size_t Write(const uint8_t *data, size_t length) = 0;

	virtual const std::vector<RawBuffer> GetReadRawBuffers() = 0;

	virtual const std::vector<RawBuffer> GetWriteRawBuffers() = 0;

	virtual const std::vector<RawBuffer> GetReadRawBuffers(RawBuffer *headerRawBuffer) = 0;

	virtual const std::vector<RawBuffer> GetWriteRawBuffers(RawBuffer *headerRawBuffer) = 0;

	virtual size_t GetReadPosition() const = 0;

	virtual bool SetReadPosition(size_t position) = 0;

	virtual size_t GetWritePosition() const = 0;

	virtual bool SetWritePosition(size_t position) = 0;

	virtual bool IsReadMarked() const = 0;
	
	virtual bool IsWriteMarked() const = 0;

	virtual bool MarkRead() = 0;

	virtual bool MarkWrite() = 0;

	virtual bool ResetRead() = 0;

	virtual bool ResetWrite() = 0;

	virtual bool UnmarkRead() = 0;

	virtual bool UnmarkWrite() = 0;
};

} } }
