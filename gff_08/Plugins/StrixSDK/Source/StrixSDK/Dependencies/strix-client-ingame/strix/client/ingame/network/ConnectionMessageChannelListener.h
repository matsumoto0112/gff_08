#pragma once

#include <strix/client/ingame/network/node/HttpSessionNodeAuthContextFactory.h>
#include <strix/client/ingame/network/StrixNetworkEvents.h>
#include <strix/net/message/MessageChannelListener.h>

#include <functional>

namespace strix { namespace client { namespace ingame { namespace network {

class ServerConnection;
typedef std::shared_ptr<ServerConnection> ServerConnectionPtr;

/**
 *  Listener that listens on message channels for server connection events
 *  and calls it's registered handlers
 */
class ConnectionMessageChannelListener : public net::message::MessageChannelListener, public std::enable_shared_from_this<ConnectionMessageChannelListener>
{
public:

	/**
	 *  Construct a listener on a server connection
	 *  @param	connection	The connection
	 */
	ConnectionMessageChannelListener(std::weak_ptr<ServerConnection> connection);

	/**
	 *  Get the server connection this listener is listening to
	 *  @returns	The connection
	 */
	const std::weak_ptr<ServerConnection> GetConnection() const;

	/**
	 *  Set the server connection this listener is listening to
	 *  @param	connection	The connection
	 */
	void SetConnection(std::weak_ptr<ServerConnection> connection);

	/**
	 *  Get the authentication context this listener's connection is using
	 *  @returns	The authentication context
	 */
	const auth::AuthContextPtr &GetAuthContext() const;

	/**
	 *  Set the authentication context this listener's connection is using
	 *  @param	authContext	The authentication context
	 */
	void SetAuthContext(auth::AuthContextPtr authContext);

	/**
	 *  Get the handler function called when the connection is ready
	 *  @returns	The handler
	 */
	const std::function<void()> &GetConnectionReadyNotifier() const;

	/**
	 *  Set the handler function called when the connection is ready
	 *  @param	connectionReadyNotifier	The handler
	 */
	void SetConnectionReadyNotifier(std::function<void()> connectionReadyNotifier);

	/**
	 *  Get the handler function called when authentication fails
	 *  @returns	The handler
	 */
	const std::function<void(int)> &GetConnectionAuthFailedNotifier() const;

	/**
	 *  Set the handler function called when authentication fails
	 *  @param	connectionAuthFailedNotifier	The handler. A function that takes an error code (int)
	 */
	void SetConnectionAuthFailedNotifier(std::function<void(int)> connectionAuthFailedNotifier);

	/**
	 *  Get the handler function called when the connection connect attempt fails
	 *  @returns	The handler
	 */
	const std::function<void(int)> &GetConnectionConnectFailedNotifier() const;

	/**
	 *  Set the handler function called when the connection connect attempt fails
	 *  @param	connectionConnectFailedNotifier	The handler. A function that takes an error code (int)
	 */
	void SetConnectionConnectFailedNotifier(std::function<void(int)> connectionConnectFailedNotifier);

	/**
	 *  Get if the connection this is listening to will authenticate on connect
	 *  @returns	The value of the authenticate on connect flag. If true, this listener will bind it's authentication handlers on connect
	 */
	const bool &GetShouldAuthenticateOnConnect() const;

	/**
	 *  Tell this listener the connection it is listening to will authenticate on connect
	 *  @param	shouldAuthenticateOnConnect	The value to set
	 */
	void SetShouldAuthenticateOnConnect(bool shouldAuthenticateOnConnect);

	/**
	 *  Called when the connection connects its message channel
	 *  @param	ev	The message channel event
	 */
	void OnConnect(const MessageChannelConnectEvent &ev) override;

	/**
	 *  Called when the connection completes its authentication
	 */
	void OnAuthComplete();

	/**
	 *  Called when the connection's authentication fails
	 *  @param	errorCode	The error code of the failure
	 *  @param	errorCategory	The error category of the failure
	 */
	void OnAuthFailed(int errorCode, core::error::ErrorCategory errorCategory);

	/**
	 *  Called when the connection sends a message
	 *  @param	ev	The message channel event
	 */
	void OnMessage(const MessageChannelMessageEvent &ev) override;

	/**
	 *  Called when the connection closes its message channel
	 *  @param	ev	The message channel event
	 */
	void OnClose(const MessageChannelCloseEvent &ev) override;

	/**
	 *  Called when the connection encounters an error on its message channel
	 *  @param	ev	The message channel event
	 */
	void OnError(const MessageChannelErrorEvent &ev) override;

	/**
	 *  Called when this listener is detached from the channel
	 */
	void OnDetach() override;

	/**
	 *  Trigger connection ready notifier and drop all connection notifiers
	 */
	void FireReadyEvent();

	/**
	 *  Trigger auth failed notifier and drop all connection notifiers	
	 *  @param	errorCode	The auth error code
	 */
	void FireAuthFailedEvent(int errorCode);

	/**
	 *  Trigger connection failed notifier and drop all connection notifiers
	 *  @param	errorCode	The connect error code
	 */
	void FireConnectFailedEvent(int errorCode);

protected:

	/**
	 *  Remove connection ready handlers
	 */
	void DropConnectionReadyHandlers();

private:
	auth::AuthContextPtr m_authContext;
	bool m_isPreparingConnection;
	bool m_shouldAuthenticateOnConnect;
	std::weak_ptr<ServerConnection> m_connection;
	std::function<void()> m_connectionReadyNotifier;
	std::function<void(int)> m_connectionAuthFailedNotifier;
	std::function<void(int)> m_connectionConnectFailedNotifier;
};

typedef std::shared_ptr<ConnectionMessageChannelListener> ConnectionMessageChannelListenerPtr;

} } } }
