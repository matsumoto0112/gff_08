#pragma once

#include <strix/net/serialization/SerializationManager.h>
#include <strix/net/serialization/serializer/SerializerImpl.h>

#include <memory>

namespace strix { namespace net { namespace serialization {

class Serialization
{
public:
	static Serialization &GetInstance();

    static SerializationManager &GetSerializationManager() {
        return *GetInstance().m_pSerializationManager;
    }

    static void SetSerializationManager(std::unique_ptr<SerializationManager> pSerializationManager) {
        GetInstance().m_pSerializationManager = std::move(pSerializationManager);
    }

	template <typename T>
	static bool Serialize(io::Encoder &encoder, const T &value) {
		return serializer::SerializerImpl<T>().Serialize(encoder, value);
	}

	template <typename T>
    static bool Deserialize(io::Decoder &decoder, T &value) {
		return serializer::SerializerImpl<T>().Deserialize(decoder, value);
    }

private:
	Serialization();

	std::unique_ptr<SerializationManager> m_pSerializationManager;
};

} } }
