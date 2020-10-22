#pragma once

#include <strix/net/io/Format.h>

#include <memory>
#include <string>

namespace strix { namespace net { namespace object {
class Object;
class MetaClass;
} } }

namespace strix { namespace net { namespace io {

class Encoder;

typedef std::shared_ptr<Encoder> EncoderPtr;

class Encoder
{
public:
	Encoder() {}
	virtual ~Encoder() {}

	virtual bool WriteNull() = 0;

	virtual bool WriteBool(bool value) = 0;

	virtual bool WriteByte(uint8_t value) = 0;

	virtual bool WriteShort(short value) = 0;

	virtual bool WriteInt(int value) = 0;

	virtual bool WriteLong(long value) = 0;

	virtual bool WriteLongLong(long long value) = 0;

	virtual bool WriteFloat(float value) = 0;

	virtual bool WriteDouble(double value) = 0;

	virtual bool WriteString(const char *value, size_t len) = 0;

	virtual bool WriteString(const std::string &value) = 0;

	virtual bool WriteBinary(const uint8_t *bytes, size_t length) = 0;
	
	virtual bool WriteObjectBegin(strix::net::io::Format format, int classId) = 0;

	virtual bool WriteObjectEnd() = 0;
	
	virtual bool WriteObjectPropertyBegin(int index, const std::string &name) = 0;

	virtual bool WriteObjectPropertyEnd(int index, const std::string &name) = 0;

	virtual bool WriteArrayBegin(int len) = 0;

	virtual bool WriteArrayItemBegin(int index) = 0;

	virtual bool WriteArrayItemEnd(int index) = 0;

	virtual bool WriteArrayEnd() = 0;

	virtual bool WriteMapBegin(int len) = 0;

	virtual bool WriteMapKeyBegin(int index) = 0;

	virtual bool WriteMapKeyEnd(int index) = 0;

	virtual bool WriteMapValueBegin(int index) = 0;

	virtual bool WriteMapValueEnd(int index) = 0;
	
	virtual bool WriteMapEnd() = 0;

	virtual bool Flush() = 0;
};

} } }
