#pragma once

#include <strix/client/ingame/auth/SessionRestoreHandler.h>

namespace strix { namespace client { namespace core { namespace auth {
class AuthClient;
typedef std::shared_ptr<AuthClient> AuthClientPtr;
} } } }

namespace strix { namespace client { namespace core { namespace session {
class SessionClient;
typedef std::shared_ptr<SessionClient> SessionClientPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace auth {

class ClientSession;
typedef std::shared_ptr<ClientSession> ClientSessionPtr;

/**
 *  Abstract session restore handler. Custom implementations can derive this class and override its protected methods to generate authentication information
 */
class AbstractSessionRestoreHandler : public SessionRestoreHandler
{
public:

    /**
     *  Send the message to restore the session
     *  @param	authToken	The auth token to use for the authentication
     *  @param	sessionClient	The session client to restore the session on
     *  @param	authClient	The auth client used with this session client
     *  @param	handler	The handler to call on successful restore
     *  @param	failureHandler	The handler to call on failure to restore
     */
    void SendSessionRestoreMessage(data::AuthToken authToken,
		core::session::SessionClientPtr sessionClient,
		core::auth::AuthClientPtr authClient,
		core::request::RequestResultHandlerT<core::session::message::RestoreSessionResponse> handler,
		core::request::RequestFailureHandler failureHandler) override;

protected:

	/**
	 *  Calculate the c nonce value for the token
	 *  @returns	The nonce value as a string
	 */
	virtual std::string GenerateCNonce() = 0;

	/**
	 *  Calculate the hash value for the token
	 *  @param	password	The user password
	 *  @param	nonce	The nonce value
	 *  @param	cnonce	The c nonce value
	 *  @returns	The hash value as a string
	 */
	virtual std::string CalculateHash(const std::string &password, const std::string &nonce, const std::string &cnonce) = 0;
};

} } } }
