#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/replica/model/Replica.h>
#include <strix/client/core/message/ParameterNotificationMessage.h>

#include <memory>

namespace strix { namespace client { namespace replica { namespace message {

/**
 *  A notfication received from the server holding information about a newly created replica 
 */
class ReplicaCreateNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(ReplicaCreateNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.replica.message.ReplicaCreateNotification")
		STRIX_PROPERTY(m_replica)
	)

	typedef std::shared_ptr<strix::client::replica::model::Replica> ReplicaPtr;

	ReplicaCreateNotification() {}

	ReplicaCreateNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	virtual ~ReplicaCreateNotification() {}

	/**
	 *  Return the new replica
	 *  @returns	The replica
	 */
	const ReplicaPtr &GetReplica() const {
		return m_replica;
	}

	/**
	 *  Set the new replica in this notification
	 *  @param	replica	The replica
	 */
	void SetReplica(const ReplicaPtr &replica) {
        m_replica = replica;
	}

private:
	ReplicaPtr m_replica;
};

typedef std::shared_ptr<ReplicaCreateNotification> ReplicaCreateNotificationPtr;

} } } }
