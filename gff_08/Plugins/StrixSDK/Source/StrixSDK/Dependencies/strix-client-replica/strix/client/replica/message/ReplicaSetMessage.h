#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/UID.h>
#include <strix/client/core/message/ParameterRequestMessage.h>

namespace strix { namespace client { namespace replica { namespace message {

class ReplicaSetMessage : public strix::client::core::message::ParameterRequestMessage
{
public:
	STRIX_CLASS(ReplicaSetMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.replica.message.ReplicaSetMessage")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_properties)
	)
		
	ReplicaSetMessage() {}

	ReplicaSetMessage(long long primaryKey) : m_primaryKey(primaryKey) {}

	ReplicaSetMessage(const MetaClass &parameterClass) : ParameterRequestMessage(parameterClass) {}

	ReplicaSetMessage(const MetaClass &parameterClass, long long primaryKey)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey) {}

	ReplicaSetMessage(const MetaClass &parameterClass, long long primaryKey, const std::map<int, net::object::ObjectPtr> &properties)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey) {}
	

	virtual ~ReplicaSetMessage() {}

	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

	std::map<int, net::object::ObjectPtr> &GetProperties() {
		return m_properties;
	}

	void SetProperties(const std::map<int, net::object::ObjectPtr> &properties) {
		m_properties = properties;
	}

private:
	long long m_primaryKey;
	std::map<int, net::object::ObjectPtr> m_properties;
};

} } } }
