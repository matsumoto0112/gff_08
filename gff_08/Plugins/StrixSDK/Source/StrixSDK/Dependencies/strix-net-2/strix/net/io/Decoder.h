#pragma once

#include <strix/net/io/Format.h>

#include <string>
#include <memory>

namespace strix { namespace net { namespace object {
class MetaClass;
class Object;
} } }

namespace strix { namespace net { namespace io {

class Decoder;

typedef std::shared_ptr<Decoder> DecoderPtr;

class Decoder
{
public:
	Decoder() {}
	virtual ~Decoder() {}

	virtual bool ReadNull() = 0;

	virtual bool GetNextFormat(Format &outFormat) = 0;

	virtual bool ReadBool(bool &value) = 0;

	virtual bool ReadByte(uint8_t &value) = 0;

	virtual bool ReadShort(short &value) = 0;

	virtual bool ReadInt(int &value) = 0;

	virtual bool ReadLong(long &value) = 0;

	virtual bool ReadLongLong(long long &value) = 0;

	virtual bool ReadFloat(float &value) = 0;

	virtual bool ReadDouble(double &value) = 0;
	
	virtual bool ReadString(char *value, size_t valueLen) = 0;

	virtual bool ReadString(std::string &value) = 0;
	
	virtual bool ReadBinaryBegin(size_t &len) = 0;

	virtual bool ReadBinary(uint8_t *value, size_t valueLen) = 0;
	
	virtual bool ReadBinaryEnd() = 0;

	virtual bool ReadObjectBegin(const object::MetaClass *&pMetaClass, Format &format) = 0;
	
	virtual bool ReadObjectEnd() = 0;

	virtual bool ReadObjectPropertyBegin(int index, std::string &name) = 0;

	virtual bool ReadObjectPropertyEnd(int index, std::string &name) = 0;

	virtual bool ReadArrayBegin(int &len) = 0;

	virtual bool ReadArrayItemBegin(int index) = 0;

	virtual bool ReadArrayItemEnd(int index) = 0;

	virtual bool ReadArrayEnd() = 0;

	virtual bool ReadMapBegin(int &len) = 0;

	virtual bool ReadMapKeyBegin(int index) = 0;

	virtual bool ReadMapKeyEnd(int index) = 0;

	virtual bool ReadMapValueBegin(int index) = 0;

	virtual bool ReadMapValueEnd(int index) = 0;
	
	virtual bool ReadMapEnd() = 0;
};

} } }
