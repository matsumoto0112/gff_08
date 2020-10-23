#pragma once

#include <strix/client/core/auth/Credentials.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultRequestMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  Request to login
 *  
 *  Strix message type - Requests sent to the server
 */
class LoginMessage : public strix::client::core::message::DefaultRequestMessage
{
public:
	STRIX_CLASS(LoginMessage, DefaultRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.LoginMessage")
		STRIX_PROPERTY(m_credentials)
	)
	
	typedef std::shared_ptr<strix::client::core::auth::Credentials> CredentialsPtr;

	LoginMessage() {}

	virtual ~LoginMessage() {}

	/**
	 *  Get the login credentials in this message
	 *  @returns	The credentials
	 */
	const CredentialsPtr &GetCredentials() const {
		return m_credentials;
	}

	/**
	 *  Set the login credentials in this message
	 *  @param	credentials	The credentials
	 */
	void SetCredentials(const CredentialsPtr &credentials) {
		m_credentials = credentials;
	}

private:
	CredentialsPtr m_credentials;
};

typedef std::shared_ptr<LoginMessage> LoginMessagePtr;

} } } } }

