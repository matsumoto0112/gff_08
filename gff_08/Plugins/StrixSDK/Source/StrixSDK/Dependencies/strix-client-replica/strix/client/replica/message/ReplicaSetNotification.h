#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/message/ParameterNotificationMessage.h>

#include <memory>

namespace strix { namespace client { namespace replica { namespace message {

/**
 *  A notfication received from the server holding information about updated properties on a replica
 */
class ReplicaSetNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(ReplicaSetNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.replica.message.ReplicaSetNotification")
		STRIX_PROPERTY(m_replicaId)
		STRIX_PROPERTY(m_properties)
	)

	ReplicaSetNotification() {}

	ReplicaSetNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	virtual ~ReplicaSetNotification() {}


	/**
	 *  Return the id of the updated replica
	 *  @returns	The id
	 */
	long long GetReplicaId() 
	{
		return m_replicaId;
	}

	/**
	 *  Set the id in this notification of the updated replica
	 *  @param	replicaId	The id
	 */
	void SetReplicaId(long long replicaId)
	{
		m_replicaId = replicaId;
	}

	/**
	 *  Return the updated properties of the replica
	 *  @returns	A map of int (property id) to object (property value)
	 */
	std::map<int, net::object::ObjectPtr> &GetProperties()
	{
		return m_properties;
	}

	/**
	 *  Set the updated properties in this notification
	 *  @param	properties	A map of int (property id) to object (property value)
	 */
	void SetProperties(const std::map<int, net::object::ObjectPtr> &properties)
	{
		m_properties = properties;
	}

private:
	long long m_replicaId;
	std::map<int, net::object::ObjectPtr> m_properties;
};

typedef std::shared_ptr<ReplicaSetNotification> ReplicaSetNotificationPtr;

} } } }
