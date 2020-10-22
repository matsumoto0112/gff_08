#pragma once

#include <strix/client/core/auth/Credentials.h>
#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace auth {

/**
 *  Credentials containing a user ID and password
 */
class IdPasswordCredentials : public Credentials
{
public:
	STRIX_CLASS(IdPasswordCredentials, Credentials)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.IdPasswordCredentials")
		STRIX_PROPERTY(m_userId)
		STRIX_PROPERTY(m_password)
	)
	
	IdPasswordCredentials() {}

	virtual ~IdPasswordCredentials() {}

	/**
	 *  Get the user ID
	 *  @returns	The user ID
	 */
	std::string &GetUserId() {
		return m_userId;
	}

	/**
	 *  Set the user ID in these credentials
	 *  @param	userId	The user ID
	 */
	void SetUserId(const std::string &userId) {
		m_userId = userId;
	}

	/**
	 *  Get the password
	 *  @returns	The password
	 */
	std::string &GetPassword() {
		return m_password;
	}

	/**
	 *  Set the password in these credentials
	 *  @param	password	The password
	 */
	void SetPassword(const std::string &password) {
		m_password = password;
	}
	
private:
	std::string m_userId;
	std::string m_password;
};

} } } }
