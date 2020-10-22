#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultResponseMessage.h>

namespace strix { namespace client { namespace core { namespace session { namespace message {

/**
 *  Response to a successful Session challenge
 *  
 *  Strix response type - Received from server after request made
 */
class SessionChallengeResponse : public strix::client::core::message::DefaultResponseMessage
{
public:
	STRIX_CLASS(SessionChallengeResponse, DefaultResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.SessionChallengeResponse")
		STRIX_PROPERTY(m_nonce)
	)

	SessionChallengeResponse() {}

	virtual ~SessionChallengeResponse() {}

	/**
	 *  Get the nonce value for authentication from the server
	 *  @returns	The nonce as a string
	 */
	std::string &GetNonce() {
		return m_nonce;
	}

	/**
	 *  Set the nonce value information
	 *  @param	nonce	The nonce value as a string
	 */
	void SetNonce(const std::string &nonce) {
		m_nonce = nonce;
	}

  private:
    std::string m_nonce;
};

typedef std::shared_ptr<SessionChallengeResponse> SessionChallengeResponsePtr;

} } } } }
