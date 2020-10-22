#pragma once

#include <strix/net/serialization/SerializationManager.h>
#include <strix/net/serialization/serializer/DynamicSerializer.h>

#include <map>
#include <memory>

namespace strix { namespace net { namespace object {
class MetaClass;
class Object;
} } }

namespace strix { namespace net { namespace serialization {

class DefaultSerializationManager : public SerializationManager
{
public:
	DefaultSerializationManager();
	
	using SerializationManager::Register;

	template <typename ValueType>
	bool RegisterImpl() {
		return Register(object::MetaClassT<ValueType>::Get(), std::make_unique<serializer::DynamicSerializerImpl<ValueType> >());
	}

	bool Register(const object::MetaClass &metaClass, std::unique_ptr<serializer::DynamicSerializer> pSerializer) override;

	bool Unregister(const object::MetaClass &metaClass) override;

    bool Serialize(io::Encoder &encoder, const object::MetaClass *pMetaClass, const void *value) override;

    bool Deserialize(io::Decoder &decoder, const object::MetaClass *pMetaClass, void *&value) override;

	serializer::DynamicSerializer *FindSerializer(const object::MetaClass *pMetaClass) override;

	io::Format MetaClassToFormat(const object::MetaClass &metaClass) override;

private:
	typedef std::map<const object::MetaClass *, std::unique_ptr<serializer::DynamicSerializer> > SerializerMap;

	SerializerMap m_serializerMap;
	std::unique_ptr<serializer::DynamicSerializer> m_defaultSerializer;
};

} } }
