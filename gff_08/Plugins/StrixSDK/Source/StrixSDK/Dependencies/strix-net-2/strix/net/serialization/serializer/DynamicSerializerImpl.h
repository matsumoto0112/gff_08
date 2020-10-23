#pragma once

#include <strix/net/serialization/serializer/DynamicSerializer.h>
#include <strix/net/serialization/serializer/SerializerImpl.h>

namespace strix { namespace net { namespace serialization { namespace serializer {

template <typename T>
class DynamicSerializerImpl : public DynamicSerializer
{
public:
	typedef SerializerImpl<T*> SerializerType;

	DynamicSerializerImpl() {}
	virtual ~DynamicSerializerImpl() {}

	bool Serialize(io::Encoder &encoder, const object::MetaClass &, const void *value) override
	{
		return m_serializer.Serialize(encoder, static_cast<const T *>(value));
	}

	bool Deserialize(io::Decoder &decoder, const object::MetaClass &, void *&value) override
	{
		T *p = static_cast<T*>(value);
		bool res = m_serializer.Deserialize(decoder, p);
		value = p;

		return res;
	}

private:
	SerializerType m_serializer;
};

} } } }
