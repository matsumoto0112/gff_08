#pragma once

#include <strix/net/stream/Stream.h>

#include <vector>

namespace strix { namespace net { namespace stream {

class FixedSizeMemoryStream : public Stream
{
public:
	FixedSizeMemoryStream(size_t size);
	virtual ~FixedSizeMemoryStream();

	const unsigned char *GetData() const {
		return m_data.data();
	}

	unsigned char *GetData() {
		return m_data.data();
	}

	void Clear() {
		m_head = 0;
		m_readableSize = 0;
	}

	void Reset()
	{
		m_head = 0;
	}

	size_t GetReadableSize() const
	{
		return m_readableSize;
	}

	size_t GetAllocatedSize() const
	{
		return m_data.size();
	}

	void SetReadableSize(size_t readableSize)
	{
		m_readableSize = readableSize;
	}

	size_t GetSize() override;

	virtual uint8_t GetByte(size_t position);

	virtual size_t Rewrite(const unsigned char *bytes, size_t length, size_t position);

	size_t Write(const unsigned char *bytes, size_t length) override;

	size_t Read(unsigned char *bytes, size_t length) override;

	virtual size_t Advance(size_t length);

private:
	std::vector<uint8_t> m_data;
	size_t m_head;
	size_t m_readableSize;
};

} } }
