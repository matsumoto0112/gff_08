#pragma once

#include <strix/net/serialization/serializer/AbstractObjectSerializer.h>

namespace strix { namespace net { namespace serialization { namespace serializer {

class GenericObjectSerializer : public AbstractObjectSerializer
{
public:
	GenericObjectSerializer();
	virtual ~GenericObjectSerializer();

	bool GetPropertyCount(const object::MetaClass &metaClass, const object::Object *value, int &count) override;

	bool SerializeProperties(io::Encoder &encoder, const object::MetaClass &metaClass, const object::Object *value) override;

	bool DeserializeProperties(io::Decoder &decoder, const object::MetaClass &metaClass, object::Object *&value) override;
};


} } } }
