#pragma once

#include <strix/net/util/msgpack/MessagePackFormat.h>
#include <strix/net/stream/Stream.h>
#include <strix/net/system/Endian.h>

namespace strix { namespace net { namespace util { namespace msgpack {

class MessagePackParser
{
public:
	MessagePackParser();

	MessagePackParser(stream::Stream *pStream);

	stream::Stream *GetStream() {
		return m_pStream;
	}

	void SetStream(stream::Stream *pStream) {
		m_pStream = pStream;
	}

	static bool IsPositiveFixInt(uint8_t byte);

	static bool IsNegativeFixInt(uint8_t byte);

	static bool IsFixMap(uint8_t byte);

	static bool IsFixArray(uint8_t byte);

	static bool IsFixStr(uint8_t byte);

	static MessagePackFormat ByteToFormat(uint8_t byte);

	bool GetHeader(MessagePackFormat &outFormat, uint8_t &outHeaderByte);

	bool ParseNil();

	bool ParseBool(bool &outValue);

	template <typename T>
	bool ParseInt(T &outValue);

	template <typename T>
	bool ParseFloat(T &outValue);

	bool ParseStringHeader(uint32_t &outLen);

	bool ReadStringBody(char *buf, size_t len);

	bool ParseBinaryHeader(uint32_t &outLen);

	bool ReadBinaryBody(uint8_t *buf, size_t len);

	bool ParseArrayHeader(uint32_t &outLen);

	bool ParseMapHeader(uint32_t &outLen);

	bool ParseExtHeader(uint32_t &outLen, int8_t &outType);

	bool ReadExtBody(uint8_t *buf, size_t len);

private:
	bool ParseHeader(MessagePackFormat &outFormat, uint8_t &outHeaderByte);
	
	bool IsHeader() const;

	void Supply(size_t size);

	void Consume(size_t size);

	template <typename T, typename U>
	bool ReadValue(U &outValue);

	stream::Stream *m_pStream;
	MessagePackFormat m_format;
	uint8_t m_headerByte;
	size_t m_data;
};

inline bool MessagePackParser::IsPositiveFixInt(uint8_t byte)
{
	return !(byte & 0x80); // 0x00 - 0x7f
}

inline bool MessagePackParser::IsNegativeFixInt(uint8_t byte)
{
	return ((byte & 0xe0) == 0xe0);  // 0xe0 - 0xff
}

inline bool MessagePackParser::IsFixMap(uint8_t byte)
{
	return ((byte & 0xf0) == 0x80); // 0x80 - 0x8f
}

inline bool MessagePackParser::IsFixArray(uint8_t byte)
{
	return ((byte & 0xf0) == 0x90); // 0x90 - 0x9f
}

inline bool MessagePackParser::IsFixStr(uint8_t byte)
{
	return ((byte & 0xe0) == 0xa0); // 0xa0 - 0xbf
}

template <typename T, typename U>
bool MessagePackParser::ReadValue(U &outValue)
{
	T v;
	if(m_pStream->Read(reinterpret_cast<unsigned char*>(&v), sizeof(v)) < sizeof(v))
		return false;

	outValue = static_cast<U>(system::BigEndian::Convert(v));
	Consume(sizeof(v));
	
	return true;
}

template <typename T>
bool MessagePackParser::ParseInt(T &outValue)
{
	uint8_t headerByte;
	if (!GetHeader(m_format, headerByte))
		return false;

	if (IsPositiveFixInt(headerByte))
	{
		outValue = headerByte;
		Consume(1);
	}
	else if(IsNegativeFixInt(headerByte))
	{
		outValue = static_cast<int8_t>(headerByte);
		Consume(1);
	}
	else
	{
		switch(headerByte)
		{
		case 0xcc:
			return ReadValue<uint8_t>(outValue);
		case 0xcd:
			return ReadValue<uint16_t>(outValue);
		case 0xce:
			return ReadValue<uint32_t>(outValue);
		case 0xcf:
			return ReadValue<uint64_t>(outValue);
		case 0xd0:
			return ReadValue<int8_t>(outValue);
		case 0xd1:
			return ReadValue<int16_t>(outValue);
		case 0xd2:
			return ReadValue<int32_t>(outValue);
		case 0xd3:
			return ReadValue<int64_t>(outValue);
		default:
			return false;
		}
	}

	return true;
}

template <typename T>
bool MessagePackParser::ParseFloat(T &outValue)
{
	uint8_t headerByte;
	if (!GetHeader(m_format, headerByte))
		return false;

	switch(headerByte)
	{
	case 0xca:
		return ReadValue<float>(outValue);
	case 0xcb:
		return ReadValue<double>(outValue);
	default:
		return false;
	}

	return true;
}

} } } }
