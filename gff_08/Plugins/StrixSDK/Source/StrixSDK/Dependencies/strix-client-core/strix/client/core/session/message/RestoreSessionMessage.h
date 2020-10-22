#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultRequestMessage.h>

namespace strix { namespace client { namespace core { namespace session { namespace message {

/**
 *  Request to restore a session with a token as authentication
 *  
 *  Strix message type - Requests sent to the server
 */
class RestoreSessionMessage : public strix::client::core::message::DefaultRequestMessage
{
public:
	STRIX_CLASS(RestoreSessionMessage, DefaultRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.RestoreSessionMessage")
		STRIX_PROPERTY(m_sessionToken)
	)

	RestoreSessionMessage() {}

	RestoreSessionMessage(const std::string &sessionToken) : m_sessionToken(sessionToken) {}

	virtual ~RestoreSessionMessage() {}

	/**
	 *  Get the session token
	 *  @returns	The session token as a string
	 */
	std::string &GetSessionToken() {
		return m_sessionToken;
	}

	/**
	 *  Set the session token
	 *  @param	sessionToken	The session token as a string
	 */
	void SetSessionToken(const std::string &sessionToken) {
		m_sessionToken = sessionToken;
	}

  private:
    std::string m_sessionToken;
};

typedef std::shared_ptr<RestoreSessionMessage> RestoreSessionMessagePtr;

} } } } }
