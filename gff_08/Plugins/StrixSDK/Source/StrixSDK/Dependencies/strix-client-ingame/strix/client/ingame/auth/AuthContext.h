#pragma once

#include <strix/client/core/error/ErrorCategory.h>

#include <functional>
#include <memory>

namespace strix { namespace net { namespace object {
class Object;
typedef std::shared_ptr<Object> ObjectPtr;
} } }

namespace strix { namespace client { namespace ingame { namespace network {
class ServerConnection;
typedef std::shared_ptr<ServerConnection> ServerConnectionPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace auth {
	
/**
 *  Base class for authentication request contexts
 */
class AuthContext
{
public:
	typedef std::function<void()> Notifier;
	typedef std::function<void(int, core::error::ErrorCategory)> ErrorCodeNotifier;

	virtual ~AuthContext() = default;

	/**
	 *  Perform authentication request
	 *  @param	connection	A server connection
	 *  @param	success	Handler to call on successful authentication action
	 *  @param	failure	Handler to call on failed authentication action. A function taking an error code and category
	 */
	virtual void PerformAuth(network::ServerConnectionPtr connection, Notifier success, ErrorCodeNotifier failure) = 0;

	/**
	 *  Return if a message is an Auth message
	 *  @param	connection	A server connection
	 *  @param	msg	The message to check
	 *  @returns	True if the message is an authentication message for this context
	 */
	virtual bool IsAuthMessage(network::ServerConnectionPtr connection, net::object::ObjectPtr msg) = 0;
};

} } } }
