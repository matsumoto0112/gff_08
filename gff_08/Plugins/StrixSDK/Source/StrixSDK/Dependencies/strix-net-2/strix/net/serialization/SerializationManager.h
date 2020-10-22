#pragma once

#include <strix/net/object/MetaClassT.h>
#include <strix/net/serialization/serializer/DynamicSerializer.h>
#include <strix/net/serialization/SerializationConfig.h>

#include <map>
#include <memory>
#include <mutex>

namespace strix { namespace net { namespace serialization {

struct ClassExtraInfo
{
	object::MetaClass::PropertyInfo *m_genericClassesArray;
	int propertyCount;

	ClassExtraInfo() : m_genericClassesArray(nullptr) {};
};

class SerializationManager
{
public:
	SerializationManager() {}
	virtual ~SerializationManager() {}

	const SerializationConfig &GetConfig() const {
		return m_config;
	}

	SerializationConfig &GetConfig() {
		return m_config;
	}

	void SetConfig(SerializationConfig &&config) {
		m_config = config;
	}

	virtual io::Format MetaClassToFormat(const  object::MetaClass &metaClass) = 0;
	
	template <typename ValueType, typename SerializerType>
	bool Register() {
		return Register(object::MetaClassT<ValueType>::Get(), std::make_unique<SerializerType>());
	}

	virtual bool Register(const object::MetaClass &metaClass, std::unique_ptr<serializer::DynamicSerializer> pSerializer) = 0;

	template <typename ValueType>
	bool Unregister() {
		return Unregister(object::MetaClassT<ValueType>::Get());
	}

	virtual bool Unregister(const object::MetaClass &metaClass) = 0;

    virtual bool Serialize(io::Encoder &encoder, const object::MetaClass *pMetaClass, const void *value) = 0;

    virtual bool Deserialize(io::Decoder &decoder, const object::MetaClass *pMetaClass, void *&value) = 0;

	virtual serializer::DynamicSerializer *FindSerializer(const object::MetaClass *pMetaClass) = 0;

	static ClassExtraInfo GetClassExtraInfo(const object::MetaClass &metaClass);

private:
	static ClassExtraInfo ExtraInfoWalker(const object::MetaClass *metaClass);

	SerializationConfig m_config;
	static std::map<object::MetaClass::ClassId, ClassExtraInfo> classExtraInfoMap;
	static std::mutex classExtraInfoMapMutex;
};

} } }
