#pragma once

#include <strix/client/ingame/auth/data/AuthToken.h>
#include <strix/client/core/request/RequestResult.h>
#include <strix/client/core/session/message/RestoreSessionResponse.h>

#include <memory>

namespace strix { namespace client { namespace core { namespace auth {
class AuthClient;
typedef std::shared_ptr<AuthClient> AuthClientPtr;
} } } }

namespace strix { namespace client { namespace core { namespace session {
class SessionClient;
typedef std::shared_ptr<SessionClient> SessionClientPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace auth {

class SessionRestoreHandler;	
typedef std::shared_ptr<SessionRestoreHandler> SessionRestoreHandlerPtr;

/**
 *  Base session restore handler. Used for restoring a session with a specific authentication method
 */
class SessionRestoreHandler
{
public:
	virtual ~SessionRestoreHandler() = default;

	/**
	 *  Create the handler
	 */
	static SessionRestoreHandlerPtr Create();

	/**
	 *  Send the message to restore the session 
	 *  @param	authToken	The auth token to use for the authentication
	 *  @param	sessionClient	The session client to restore the session on
	 *  @param	authClient	The auth client used with this session client
	 *  @param	handler	The handler to call on successful restore
	 *  @param	failureHandler	The handler to call on failure to restore
	 */
	 virtual void SendSessionRestoreMessage(data::AuthToken authToken,
						      core::session::SessionClientPtr sessionClient,
						      core::auth::AuthClientPtr authClient,
						      core::request::RequestResultHandlerT<core::session::message::RestoreSessionResponse> handler,
						      core::request::RequestFailureHandler failureHandler) = 0;
};

} } } }
