#pragma once

#include <strix/net/stream/Stream.h>

#include <utility>
#include <vector>

namespace strix { namespace net { namespace stream {

class MemoryStream : public Stream
{
public:
	MemoryStream();
	MemoryStream(size_t size);
	MemoryStream(const std::vector<uint8_t> &data);
	MemoryStream(std::vector<uint8_t> &&data);
	virtual ~MemoryStream();

	const unsigned char *GetData() const {
		return &m_data[0];
	}

	unsigned char *GetData() {
		return &m_data[0];
	}

	void SetData(std::vector<uint8_t> &&data) {
		m_data = std::move(data);
	}
	
	void SetData(const std::vector<uint8_t> &data) {
		m_data = data;
	}

	void SetData(const unsigned char *data, size_t len) {
		m_data.assign(data, data + len);
	}

	void Clear() {
		m_head = 0;
		m_data.clear();
	}

	void Resize(size_t size) {
		m_data.resize(size + m_head);
	}

	void Reserve(size_t size) {
		m_data.reserve(size + m_head);
	}

	size_t GetSize() override;

	size_t Write(const unsigned char *bytes, size_t length) override;

	size_t Read(unsigned char *bytes, size_t length) override;

private:
	std::vector<uint8_t> m_data;
	size_t m_head;
};

} } }
