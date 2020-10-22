#pragma once

#include <strix/net/serialization/serializer/DynamicSerializer.h>

namespace strix { namespace net { namespace serialization { namespace serializer {

class ObjectSerializer : public DynamicSerializer
{
public:
	ObjectSerializer() {}
	virtual ~ObjectSerializer() {}

	virtual bool CountProperties(const object::MetaClass &metaClass, const object::Object *value, int &count) = 0;

	virtual bool SerializeObject(io::Encoder &encoder, const object::MetaClass &metaClass, const object::Object *value) = 0;

	virtual bool DeserializeObject(io::Decoder &decoder, const object::MetaClass &metaClass, object::Object *&value) = 0;
};


} } } }
