#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace auth { namespace token {

/**
 *  Message secured by a token
 *  
 *  Strix message type - Requests sent to the server
 */
class TokenSecuredMessage : public strix::net::object::Object
{
public:
	STRIX_CLASS(TokenSecuredMessage, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.token.TokenSecuredMessage")
		STRIX_PROPERTY(m_token)
		STRIX_PROPERTY(m_message)
	)

	TokenSecuredMessage() {}

	virtual ~TokenSecuredMessage() {}

	/**
	 *  Get the token for this message as bytes
	 *  @returns	The token
	 */
	const std::vector<uint8_t> &GetToken() const {
		return m_token;
	}
	/**
	 *  Set the token for this message
	 *  @param	token	The token as bytes
	 */
	void SetToken(const std::vector<uint8_t> &token) {
		m_token = token;
	}

	/**
	 *  Get the actual message this object wraps
	 *  @returns	The message
	 */
	const strix::net::object::ObjectPtr &GetWrappedMessage() const {
		return m_message;
	}

	/**
	 *  Set the actual message to wrap
	 *  @param	message	The message to wrap
	 */
	void SetWrappedMessage(const strix::net::object::ObjectPtr &message) {
		m_message = message;
	}

private:
	std::vector<uint8_t> m_token;
	strix::net::object::ObjectPtr m_message;
};

} } } } }

