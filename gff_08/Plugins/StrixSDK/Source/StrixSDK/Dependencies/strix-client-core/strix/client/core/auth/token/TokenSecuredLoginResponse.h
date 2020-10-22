#pragma once

#include <strix/client/core/auth/message/LoginResponse.h>
#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace auth { namespace token {

/**
 *  Response to a successful token-secured login request. Contains a secure token
 *  
 *  Strix response type - Received from server after request made
 */
class TokenSecuredLoginResponse : public strix::client::core::auth::message::LoginResponse
{
public:
	STRIX_CLASS(TokenSecuredLoginResponse, LoginResponse)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.token.TokenSecuredLoginResponse")
		STRIX_PROPERTY(m_token)
	)

	TokenSecuredLoginResponse() {}

	virtual ~TokenSecuredLoginResponse() {}

	/**
	 *  Get the new token
	 *  @returns	The token
	 */
	const std::vector<uint8_t> &GetToken() const {
		return m_token;
	}

	/**
	 *  Set the token in this response
	 *  @param	token	The token
	 */
	void SetToken(const std::vector<uint8_t> &token) {
		m_token = token;
	}

private:
	std::vector<uint8_t> m_token;
};

} } } } }

