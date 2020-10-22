#pragma once

#include <strix/net/serialization/serializer/DynamicSerializer.h>

namespace strix { namespace net { namespace serialization { namespace serializer {

class NullSerializer : public DynamicSerializer
{
public:
	NullSerializer() {}
	virtual ~NullSerializer() {}

	bool Serialize(io::Encoder &encoder, const object::MetaClass &metaClass, const void *value) override;

	bool Deserialize(io::Decoder &decoder, const object::MetaClass &metaClass, void *&value) override;
};

} } } }
