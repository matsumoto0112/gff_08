#pragma once

#include <strix/net/io/Decoder.h>
#include <strix/net/util/msgpack/MessagePackParser.h>

#include <string>

namespace strix { namespace net { namespace io { namespace msgpack {

class MessagePackDecoder : public Decoder
{
public:
	MessagePackDecoder();
	virtual ~MessagePackDecoder();
		
	stream::Stream *GetStream() {
		return m_parser.GetStream();
	}

	void SetStream(stream::Stream *pStream) {
		m_parser.SetStream(pStream);
	}

	bool GetNextFormat(Format &outFormat) override;

	bool ReadNull() override;
	
	bool ReadBool(bool &value) override;

	bool ReadByte(uint8_t &value) override;

	bool ReadShort(short &value) override;

	bool ReadInt(int &value) override;

	bool ReadLong(long &value) override;

	bool ReadLongLong(long long &value) override;

	bool ReadFloat(float &value) override;

	bool ReadDouble(double &value) override;

	bool ReadString(char *value, size_t valueLen) override;

	bool ReadString(std::string &value) override;

	bool ReadBinaryBegin(size_t &len) override;

	bool ReadBinary(uint8_t *value, size_t valueLen) override;
	
	bool ReadBinaryEnd() override;

	bool ReadObjectBegin(const object::MetaClass *&pMetaClass, Format &format) override;
	
	bool ReadObjectEnd() override;

	bool ReadObjectPropertyBegin(int index, std::string &name) override;

	bool ReadObjectPropertyEnd(int index, std::string &name) override;

	bool ReadArrayBegin(int &len) override;
	
	bool ReadArrayItemBegin(int index) override;

	bool ReadArrayItemEnd(int index) override;

	bool ReadArrayEnd() override;

	bool ReadMapBegin(int &len) override;

	bool ReadMapKeyBegin(int index) override;

	bool ReadMapKeyEnd(int index) override;

	bool ReadMapValueBegin(int index) override;

	bool ReadMapValueEnd(int index) override;
	
	bool ReadMapEnd() override;

private:
	struct Context;

	bool Read(uint8_t *bytes, size_t length);

	bool ReadObjectHeader(Format &format, int32_t &classId);
	
	util::msgpack::MessagePackParser m_parser;
	uint8_t m_headerByte;
	bool m_isHeader;
};

} } } }
