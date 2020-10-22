#pragma once

#include <strix/client/ingame/auth/AuthContext.h>

namespace strix { namespace client { namespace ingame { namespace auth {

/**
 *  Authentication context for logging in with an application ID
 */
class ApplicationIdAuthContext : public AuthContext
{
public:

	/**
	 *  Construct an ApplicationIdAuthContext for the specified applicationId
	 *  @param	applicationId	The application id as a string
	 */
	ApplicationIdAuthContext(std::string applicationId);

	/**
	 *  Perform a login attempt with a random client ID on the specified connection. The callbacks will be called on success/failure
	 *  @param	connection	The server connection
	 *  @param	success	The success handler
	 *  @param	failure	The failure handler. A function that takes an error code and category
	 */
	void PerformAuth(network::ServerConnectionPtr connection, Notifier success, ErrorCodeNotifier failure) override;

	/**
	 *  Return if a message is an Auth message
	 *  @param	connection	A server connection
	 *  @param	msg	The message to check
	 *  @returns	True if the message is an authentication message for this context
	 */
	bool IsAuthMessage(network::ServerConnectionPtr connection, net::object::ObjectPtr msg) override;
private:
	std::string m_applicationId;
};

} } } }
