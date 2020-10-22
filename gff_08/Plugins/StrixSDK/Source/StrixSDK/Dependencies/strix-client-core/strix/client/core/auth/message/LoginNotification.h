#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultNotificationMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
*  Notification of a player login
*  
*  Strix notification type - Received when another player performed some action
*/
class LoginNotification : public strix::client::core::message::DefaultNotificationMessage
{
public:
	STRIX_CLASS(LoginNotification, DefaultNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.LoginNotification")
		STRIX_PROPERTY(m_uid)
	)

	LoginNotification() {}

	virtual ~LoginNotification() {}
	
	/**
	 *  Get the UID for the player that logged in
	 *  @returns	The UID
	 */
	const UIDPtr &GetUid() const {
	    return m_uid;
	}

	/**
	 *  Set the UID in this message
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) {
	    m_uid = uid;
	}

private:
	UIDPtr m_uid;
};

typedef std::shared_ptr<LoginNotification> LoginNotificationPtr;

} } } } }

