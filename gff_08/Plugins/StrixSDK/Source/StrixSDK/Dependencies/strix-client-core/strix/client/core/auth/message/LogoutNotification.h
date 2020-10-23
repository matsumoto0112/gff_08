#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultNotificationMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  Notification that a player has logged out
 *  
 *  Strix notification type - Received when another player performed some action
 */
class LogoutNotification : public strix::client::core::message::DefaultNotificationMessage
{
public:
	STRIX_CLASS(LogoutNotification, DefaultNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.LogoutNotification")
		STRIX_PROPERTY(m_uid)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	LogoutNotification() {}

	virtual ~LogoutNotification() {}

	/**
	 *  Get the UID of the player that logged out
	 *  @returns	The UID
	 */
	const UIDPtr &GetUid() const {
		return m_uid;
	}

	/**
	 *  Set the UID in this notification
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) {
		m_uid = uid;
	}

private:
	UIDPtr m_uid;
};

typedef std::shared_ptr<LogoutNotification> LogoutNotificationPtr;

} } } } }

