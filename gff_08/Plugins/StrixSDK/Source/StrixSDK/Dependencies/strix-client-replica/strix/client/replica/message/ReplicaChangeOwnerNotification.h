#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/UID.h>
#include <strix/client/core/message/ParameterNotificationMessage.h>

#include <memory>

namespace strix { namespace client { namespace replica { namespace message {

/**
 *  A notification that a replica has changed owner
 */
class ReplicaChangeOwnerNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(ReplicaChangeOwnerNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.replica.message.ReplicaChangeOwnerNotification")
		STRIX_PROPERTY(m_replicaId)
		STRIX_PROPERTY(m_ownerUid)
	)

	ReplicaChangeOwnerNotification() {}

	ReplicaChangeOwnerNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	virtual ~ReplicaChangeOwnerNotification() {}

	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	/**
	 *  Return the id of the replica this notification relates to
	 *  @returns	The id
	 */
    long long GetReplicaId() {
        return m_replicaId;
    }

	/**
	 *  Set the replica id this notification relates to
	 *  @param	replicaId	The id
	 */
    void SetReplicaId(long long replicaId) {
        m_replicaId = replicaId;
    }

	/**
	 *  Return the owner uid of the replica this notification relates to
	 *  @returns	The owner uid
	 */
	const UIDPtr &GetOwnerUid() const {
		return m_ownerUid;
	}

	/**
	 *  Set the owner uid of the replica this notification relates to
	 *  @param	The owner uid
	 */
	void SetOwnerUid(const UIDPtr &ownerUid) {
        m_ownerUid = ownerUid;
	}

private:
  long long m_replicaId;
  UIDPtr m_ownerUid;
};

typedef std::shared_ptr<ReplicaChangeOwnerNotification> ReplicaChangeOwnerNotificationPtr;

} } } }
