#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultResponseMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  A successful response to a request to login
 *  
 *  Strix response type - Received from server after request made
 */
class LoginResponse : public strix::client::core::message::DefaultResponseMessage
{
public:
	STRIX_CLASS(LoginResponse, DefaultResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.LoginResponse")
		STRIX_PROPERTY(m_uid)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	LoginResponse() {}

	LoginResponse(const UIDPtr &uid) : m_uid(uid) {}

	virtual ~LoginResponse() {}
	
	/**
	 *  Get the new UID for the player that made the request
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

typedef std::shared_ptr<LoginResponse> LoginResponsePtr;

} } } } }

