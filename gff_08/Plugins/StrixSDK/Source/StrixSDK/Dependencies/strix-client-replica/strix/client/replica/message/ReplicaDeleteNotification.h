#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/ParameterNotificationMessage.h>

#include <memory>

namespace strix { namespace client { namespace replica { namespace message {

/**
 *  A notfication received from the server holding information about a recently deleted replica
 */
class ReplicaDeleteNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(ReplicaDeleteNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.replica.message.ReplicaDeleteNotification")
		STRIX_PROPERTY(m_replicaId)
	)

	ReplicaDeleteNotification() {}

	ReplicaDeleteNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	virtual ~ReplicaDeleteNotification() {}

	/**
	 *  Return the id of the deleted replica
	 *  @returns	The id
	 */
	long long GetReplicaId() {
		return m_replicaId;
	}

	/**
	 *  Set the id in this notification of the deleted replica
	 *  @param	replicaId	The id
	 */
	void SetReplicaId(long long replicaId) {
        m_replicaId = replicaId;
	}

private:
	long long m_replicaId;
};

typedef std::shared_ptr<ReplicaDeleteNotification> ReplicaDeleteNotificationPtr;

} } } }
