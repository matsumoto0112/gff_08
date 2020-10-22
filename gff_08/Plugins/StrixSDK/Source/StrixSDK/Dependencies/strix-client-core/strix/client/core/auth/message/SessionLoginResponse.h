#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/auth/message/LoginResponse.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  A successful response to a session login request
 *
 *  Strix response type - Received from server after request made
 */
class SessionLoginResponse : public LoginResponse
{
public:
	STRIX_CLASS(SessionLoginResponse, LoginResponse)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.SessionLoginResponse")
		STRIX_PROPERTY(m_sessionId)
		STRIX_PROPERTY(m_sessionPassword)
	)

	SessionLoginResponse() {}

  SessionLoginResponse(const UIDPtr &uid, const std::string &sessionId, const std::string &sessionPassword) : LoginResponse(uid), m_sessionId(sessionId), m_sessionPassword(sessionPassword) {}

	virtual ~SessionLoginResponse() {}

	/**
	 *  Get the session id as a string
	 *  @returns	The session id
	 */
	std::string &GetSessionId() {
		return m_sessionId;
	}

	/**
	 *  Set the session id as a string
	 *  @param	sessionId	The session id
	 */
	void SetSessionId(const std::string &sessionId) {
		m_sessionId = sessionId;
	}

	/**
	 *  Get the session password as a string
	 *  @returns	The session password
	 */
	std::string &GetSessionPassword() {
		return m_sessionPassword;
	}

	/**
	 *  Set the session password as a string
	 *  @param	sessionPassword	The password
	 */
	void SetSessionPassword(const std::string &sessionPassword) {
		m_sessionPassword = sessionPassword;
	}

private:
	std::string m_sessionId;
	std::string m_sessionPassword;
};

typedef std::shared_ptr<SessionLoginResponse> SessionLoginResponsePtr;

} } } } }
