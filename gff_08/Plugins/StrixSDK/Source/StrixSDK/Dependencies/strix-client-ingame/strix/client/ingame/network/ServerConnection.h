#pragma once

#include <memory>
#include <functional>

namespace strix { namespace net { namespace channel {
enum class Protocol;
} } }

namespace strix { namespace net { namespace message {
class MessageChannel;
class MessageChannelListener;
typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
typedef std::shared_ptr<MessageChannelListener> MessageChannelListenerPtr;
} } }

namespace strix { namespace client { namespace core { namespace auth {
class AuthClient;
typedef std::shared_ptr<AuthClient> AuthClientPtr;
} } } }

namespace strix { namespace client { namespace core { namespace message {
class DefaultParameterMessageDispatcher;
typedef std::shared_ptr<DefaultParameterMessageDispatcher> DefaultParameterMessageDispatcherPtr;
} } } }

namespace strix { namespace client { namespace core { namespace session {
class SessionClient;
typedef std::shared_ptr<SessionClient> SessionClientPtr;
} } } }

namespace strix { namespace client { namespace core { namespace request {
class RequestDispatcher;
class RequestMessageChannelListener;
typedef std::shared_ptr<RequestDispatcher> RequestDispatcherPtr;
typedef std::shared_ptr<RequestMessageChannelListener> RequestMessageChannelListenerPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace network {

/**
 *  Base controller class for connection to a server.
 *  Provides methods for initializing the connection, processing messages 
 *  on the connection, and handling channel errors
 */
class ServerConnection
{
public:
	typedef std::function<void()> ConnectSuccessCallback;
	typedef std::function<void(int)> ConnectFailureCallback;

	ServerConnection();
	virtual ~ServerConnection();

	/**
	 *  Setup the connection with the given message channel and protocol
	 *  @param	messageChannel	The channel this connection is on
	 *  @param	protocol	The protocol to use
	 */
	virtual void Init(net::message::MessageChannelPtr messageChannel, net::channel::Protocol protocol);

	/**
	 *  Process the connection
	 */
	virtual void Process();

	/**
	 *  Disconnect the connection
	 */
	virtual void Disconnect();

	/**
	 *  Called when the underlying message channel closes
	 */
	virtual void OnChannelClose();

	/**
	 *  Called when the underlying message channel encounters an error
	 *  @param	errorCode	The error code of the error
	 */
	virtual void OnChannelError(int errorCode);

	/**
	 *  Get the authentication client this connection uses
	 *  @returns	The client
	 */
	core::auth::AuthClientPtr GetAuthClient() const;

	/**
	 *  Get the session client this connection uses
	 *  @returns	The client
	 */
	core::session::SessionClientPtr GetSessionClient() const;

	/**
	 *  Get the underlying message channel
	 *  @returns	The channel
	 */
	net::message::MessageChannelPtr GetMessageChannel() const;

	/**
	 *  Get the request dispatcher this connection uses
	 *  @returns	The dispatcher
	 */
	core::request::RequestDispatcherPtr GetRequestDispatcher() const;

	/**
	 *  Get the message dispatcher this connection uses
	 *  @returns	The dispatcher
	 */
	core::message::DefaultParameterMessageDispatcherPtr GetMessageDispatcher() const;

	/**
	 *  Check if this connection is currently open
	 *  @returns	True if the connection is open
	 */
	bool IsOpen() const;

	/**
	 *  Get the hostname of the server
	 *  @returns	The hostname
	 */
	const std::string &GetHost() const;

	/**
	 *  Get the port number of the server connection
	 *  @returns	The port number
	 */
	int GetPortNumber() const;

	/**
	 *  Get the protocol this connection uses
	 *  @returns	The protocol
	 */
	net::channel::Protocol GetProtocol() const;

protected:
	core::auth::AuthClientPtr m_authClient;
	core::session::SessionClientPtr m_sessionClient;

	net::channel::Protocol m_protocol;
	net::message::MessageChannelPtr m_messageChannel;

	core::request::RequestDispatcherPtr m_requestDispatcher;
	core::message::DefaultParameterMessageDispatcherPtr m_messageDispatcher;
	core::request::RequestMessageChannelListenerPtr m_dispatcherAdapterListener;
};

typedef std::shared_ptr<ServerConnection> ServerConnectionPtr;
typedef std::weak_ptr<ServerConnection> ServerConnectionWeakPtr;

} } } }
