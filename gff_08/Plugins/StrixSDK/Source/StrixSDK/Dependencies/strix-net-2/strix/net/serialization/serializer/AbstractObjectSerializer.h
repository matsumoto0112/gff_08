#pragma once

#include <strix/net/serialization/serializer/ObjectSerializer.h>

namespace strix { namespace net { namespace serialization { namespace serializer {

class AbstractObjectSerializer : public ObjectSerializer
{
public:
	AbstractObjectSerializer() {}
	virtual ~AbstractObjectSerializer() {}
	
	virtual object::Object *CreateObject(const object::MetaClass &metaClass);
	
	bool CountProperties(const object::MetaClass &metaClass, const object::Object *value, int &count) override;

	virtual bool GetPropertyCount(const object::MetaClass &metaClass, const object::Object *value, int &count) = 0;

	bool Serialize(io::Encoder &encoder, const object::MetaClass &metaClass, const void *value) override;

	bool SerializeObject(io::Encoder &encoder, const object::MetaClass &metaClass, const object::Object *value) override;

	virtual bool SerializeProperties(io::Encoder &encoder, const object::MetaClass &metaClass, const object::Object *value) = 0;

	bool Deserialize(io::Decoder &decoder, const object::MetaClass &metaClass, void *&value) override;

	bool DeserializeObject(io::Decoder &decoder, const object::MetaClass &metaClass, object::Object *&value) override;

	virtual bool DeserializeProperties(io::Decoder &decoder, const object::MetaClass &metaClass, object::Object *&value) = 0;

private:
	ObjectSerializer *GetSuperclassSerializer(const object::MetaClass *pSuperClass);
};


} } } }
