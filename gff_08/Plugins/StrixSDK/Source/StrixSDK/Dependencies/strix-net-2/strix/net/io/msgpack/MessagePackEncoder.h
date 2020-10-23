#pragma once

#include <strix/net/io/Encoder.h>
#include <strix/net/io/Format.h>
#include <strix/net/stream/Stream.h>

#include <ios>
#include <string>

namespace strix { namespace net { namespace io { namespace msgpack {

class MessagePackEncoder : public Encoder
{
public:
	MessagePackEncoder();
	MessagePackEncoder(stream::Stream *pStream) {
		SetStream(pStream);
	}
	virtual ~MessagePackEncoder();

	stream::Stream *GetStream() {
		return m_stream.m_pStream;
	}

	const stream::Stream *GetStream() const {
		return m_stream.m_pStream;
	}

	void SetStream(stream::Stream *pStream) {
		m_stream.m_pStream = pStream;
	}

	bool WriteNull() override;

	bool WriteBool(bool value) override;
	
	bool WriteByte(uint8_t value) override;

	bool WriteShort(short value) override;

	bool WriteInt(int value) override;

	bool WriteLong(long value) override;

	bool WriteLongLong(long long value) override;

	bool WriteFloat(float value) override;

	bool WriteDouble(double value) override;

	bool WriteString(const char *value, size_t len) override;

	bool WriteString(const std::string &value) override;

	bool WriteBinary(const uint8_t *bytes, size_t length) override;
	
	bool WriteObjectBegin(strix::net::io::Format format, int classId) override;

	bool WriteObjectEnd() override;
	
	bool WriteObjectPropertyBegin(int index, const std::string &name) override;

	bool WriteObjectPropertyEnd(int index, const std::string &name) override;

	bool WriteArrayBegin(int len) override;

	bool WriteArrayItemBegin(int index) override;

	bool WriteArrayItemEnd(int index) override;

	bool WriteArrayEnd() override;

	bool WriteMapBegin(int len) override;

	bool WriteMapKeyBegin(int index) override;

	bool WriteMapKeyEnd(int index) override;

	bool WriteMapValueBegin(int index) override;

	bool WriteMapValueEnd(int index) override;
	
	bool WriteMapEnd() override;

	bool Flush() override;

private:
	class StreamAdapter
	{
	public:
		StreamAdapter();

		void write(const char* s, std::streamsize n);

		stream::Stream *m_pStream;
		bool m_result;
	};

	StreamAdapter m_stream;
};

} } } }
