#pragma once

namespace strix { namespace net { namespace io {
class Encoder;
class Decoder;
} } }

namespace strix { namespace net { namespace object {
class MetaClass;
class Object;
} } }

namespace strix { namespace net { namespace serialization { namespace serializer {

class DynamicSerializer
{
public:
	DynamicSerializer() {}
	virtual ~DynamicSerializer() {}

	virtual bool Serialize(io::Encoder &encoder, const object::MetaClass &metaClass, const void *value) = 0;

	virtual bool Deserialize(io::Decoder &decoder, const object::MetaClass &metaClass, void *&value) = 0;
};

} } } }
