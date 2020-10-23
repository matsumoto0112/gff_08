#pragma once

#include <iterator>
#include <strix/client/core/auth/Credentials.h>
#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace auth {

/**
 *  Credentials for login with application ID. 
 *  
 *  Creates token from hash of client ID and app ID
 */
class ApplicationIdCredentials : public Credentials
{
public:
	STRIX_CLASS(ApplicationIdCredentials, Credentials)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.ApplicationIdCredentials")
		STRIX_PROPERTY(m_token)
		STRIX_PROPERTY(m_clientId)
		STRIX_PROPERTY(m_version)
	)

	ApplicationIdCredentials() {}

	ApplicationIdCredentials(const std::string &applicationId, const std::vector<uint8_t> &clientId);

	virtual ~ApplicationIdCredentials() {}

    /**
     *  Get the token
     *  @returns	The token
     */
    const std::vector<uint8_t> &GetToken() const {
	 return m_token;
    }

    /**
    *  Set the token
    *  @param	token	The token
    */
    void SetToken(const std::vector<uint8_t> &token) {
	 m_token = token;
    }

    /**
    *  Get the client ID
    *  @returns	The client ID
    */
    const std::vector<uint8_t> &GetClientId() const {
	 return m_clientId;
    }

    /**
     *  Set the client ID
     *  @param	clientId	The client ID
     */
    void SetClientId(const std::vector<uint8_t> &clientId) {
	 m_clientId = clientId;
    }

    /**
     *  Get the app version
     *  @returns	The app version number
     */
    long long GetVersion() const {
	     return m_version;
    }

    /**
     *  Set the app version
     *  @param	version	The version number
     */
    void SetVersion(long long version) {
	     m_version = version;
    }

    /**
     *  Creates an ApplicationIdCredentials with a random client ID and no token
     *  @param	applicationId	The app id
     *  @param	byteArrayLength	The length in bytes of the client ID to generate
     *  @returns	An ApplicationIdCredentials with a random client ID
     */
    static std::shared_ptr<ApplicationIdCredentials> CreateWithRandomClientId(const std::string &applicationId, int byteArrayLength);

private:
	std::vector<uint8_t> m_token;
	std::vector<uint8_t> m_clientId;
	long long m_version;
};

} } } }
