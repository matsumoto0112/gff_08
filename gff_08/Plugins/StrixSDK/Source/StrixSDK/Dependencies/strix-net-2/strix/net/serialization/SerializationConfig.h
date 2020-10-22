#pragma once

#include <strix/net/util/EncodingConverter.h>

#include <memory>
#include <utility>

namespace strix { namespace net { namespace serialization {

class SerializationConfig
{
public:
	SerializationConfig();
	SerializationConfig(SerializationConfig &&rhs) = default;

	~SerializationConfig() {}

	const std::unique_ptr<util::EncodingConverter> &GetEncodingConverter() const {
		return m_pEncodingConverter;
	}

	void SetEncodingConverter(std::unique_ptr<util::EncodingConverter> &&pEncodingConverter) {
		m_pEncodingConverter = std::move(pEncodingConverter);
	}

	SerializationConfig &operator=(SerializationConfig &rhs) {
		m_pEncodingConverter = std::move(rhs.m_pEncodingConverter);
		return *this;
	}

private:
	std::unique_ptr<util::EncodingConverter> m_pEncodingConverter;
};

} } }
