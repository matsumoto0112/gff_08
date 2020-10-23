#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultFailureMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  Informs a player they are not permitted to make the specified request (e.g not logged in)
 *  
 *  Strix response type - Received from server after request made
 */
class PermissionDeniedMessage : public strix::client::core::message::DefaultFailureMessage
{
public:
	STRIX_CLASS(PermissionDeniedMessage, DefaultFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.PermissionDeniedMessage")
		STRIX_PROPERTY(m_uid)
		STRIX_PROPERTY(m_messageType)
	)

	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	PermissionDeniedMessage() {}

	virtual ~PermissionDeniedMessage() {}

	/**
	 *  Get the UID of the player who made the request
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

	/**
	 *  Get the meta class of the message that this message is responding to
	 *  @returns	The meta class of the message
	 */
	const strix::net::object::MetaClass &GetMessageType() const {
		return *m_messageType;
	}

	/**
	 *  Set the meta class of the message this message is responding to
	 *  @param	messageType	The meta class of the message
	 */
	void SetMessageType(const strix::net::object::MetaClass &messageType) {
		m_messageType = &messageType;
	}

private:
	UIDPtr m_uid;
	const strix::net::object::MetaClass *m_messageType;
};

typedef std::shared_ptr<PermissionDeniedMessage> PermissionDeniemMessagePtr;

} } } } }

