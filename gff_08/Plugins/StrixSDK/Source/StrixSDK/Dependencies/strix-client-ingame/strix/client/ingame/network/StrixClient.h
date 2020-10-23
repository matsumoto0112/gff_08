#pragma once

#include <strix/client/ingame/network/StrixNetworkEvents.h>
#include <strix/client/core/connection/HandshakeHandlers.h>

namespace strix { namespace net { namespace channel {
enum class Protocol;
} } }

namespace strix { namespace net { namespace message {
class MessageChannelProcessor;
} } }

namespace strix { namespace client { namespace core { namespace connection {
class ReconnectableMessageChannelProcessor;
} } } }

namespace strix { namespace client { namespace core { namespace http {
class HttpClient;
typedef std::shared_ptr<HttpClient> HttpClientPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace auth {
class AuthContext;
typedef std::shared_ptr<AuthContext> AuthContextPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace network { namespace node {
class NodeAuthContextFactory;
typedef std::shared_ptr<NodeAuthContextFactory> NodeAuthContextFactoryPtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace network {

class ServerConnection;
class MasterServerConnection;
class RoomServerConnection;
class ConnectionMessageChannelListener;
typedef std::shared_ptr<ServerConnection> ServerConnectionPtr;
typedef std::weak_ptr<ServerConnection> ServerConnectionWeakPtr;
typedef std::shared_ptr<MasterServerConnection> MasterServerConnectionPtr;
typedef std::shared_ptr<RoomServerConnection> RoomServerConnectionPtr;
typedef std::shared_ptr<ConnectionMessageChannelListener> ConnectionMessageChannelListenerPtr;

class StrixClient;
typedef std::shared_ptr<StrixClient> StrixClientPtr;
typedef std::weak_ptr<StrixClient> StrixClientWeakPtr;

/**
 *  High level client controller for connecting to room and master servers
 */
class StrixClient : public std::enable_shared_from_this<StrixClient>
{
public:
	StrixClient();

	virtual ~StrixClient();

	/**
	 *  Construct a StrixClient with an application ID
	 *  @param	applicationId	The id to use
	 */
	static StrixClientPtr CreateWithApplicationIdAuth(std::string applicationId);

	/**
	 *  Construct a StrixClient with an HTTP access token
	 *  @param	applicationId	The id to use
	 *  @param	accessToken	The token to use
	 *  @param	httpClient	The HTTP client to perform the authentication with
	 */
	static StrixClientPtr CreateWithHttpAccessTokenAuth(std::string applicationId,
	                                                    std::string accessToken,
	                                                    core::http::HttpClientPtr httpClient);

	/**
	 *  Get the default authentication context for the room server
	 *  @returns	The context
	 */
	auth::AuthContextPtr GetDefaultRoomAuthContext() const;

	/**
	 *  Set the default authentication context for the room server
	 *  @param	defaultRoomAuth	The context
	 */
	void SetDefaultRoomAuthContext(auth::AuthContextPtr defaultRoomAuth);

	/**
	 *  Get the default authentication context for the master server
	 *  @returns	The context
	 */
	auth::AuthContextPtr GetDefaultMasterAuthContext() const;

	/**
	 *  Set the default authentication context for the master server
	 *  @param	defaultMasterAuth	The context
	 */
	void SetDefaultMasterAuthContext(auth::AuthContextPtr defaultMasterAuth);

	/**
	 *  Get the default authentication context factory
	 *  @returns	The factory
	 */
	node::NodeAuthContextFactoryPtr GetDefaultNodeAuthContextFactory() const;

	/**
	 *  Set the default authentication context factory
	 *  @param	defaultNodeAuthContextFactory	The factory
	 */
	void SetDefaultNodeAuthContextFactory(node::NodeAuthContextFactoryPtr defaultNodeAuthContextFactory);

	/**
	 *  Process pending operations on this client
	 */
	void Process();

	/**
	 *  Connect to a room server. Callbacks are called on success/failure. Success callback args return the connection, so keep in scope or connection will be lost
	 *  @param	host	The hostname of the server
	 *  @param	portNumber	The port number to connect to
	 *  @param	successHandler	The handler to call on successful connect. A function that takes a RoomServerConnectEventArgs as input
	 *  @param	failureHandler	The handler to call on a failed connect. A function that takes a ServerConnectFailedEventArgs as input
	 *  @param	authContext	Optional authentication context to use instead of the default
	 */
	void ConnectToRoomServer(std::string host, int portNumber, net::channel::Protocol protocol,
	                         std::function<void(RoomServerConnectEventArgs)> successHandler,
	                         std::function<void(ServerConnectFailedEventArgs)> failureHandler,
	                         auth::AuthContextPtr authContext = nullptr);

	/**
	 *  Connect to a master server. Callbacks are called on success/failure. Success callback args return the connection, so keep in scope or connection will be lost
	 *  @param	host	The hostname of the server
	 *  @param	portNumber	The port number to connect to
	 *  @param	successHandler	The handler to call on successful connect. A function that takes a MasterServerConnectEventArgs as input
	 *  @param	failureHandler	The handler to call on a failed connect. A function that takes a ServerConnectFailedEventArgs as input
	 *  @param	authContext	Optional authentication context to use instead of the default
	 */
	void ConnectToMasterServer(std::string host, int portNumber,
	                           std::function<void(MasterServerConnectEventArgs)> successHandler,
	                           std::function<void(ServerConnectFailedEventArgs)> failureHandler,
	                           auth::AuthContextPtr authContext = nullptr);

protected:

	/**
	 *  Build a reconnectable message channel processor for the master message channel
	 *  @returns	A channel processor
	 */
	virtual std::unique_ptr<core::connection::ReconnectableMessageChannelProcessor> BuildMasterMessageChannelProcessor();

	/**
	 *  Build a message channel processor for the room message channel
	 *  @returns	A channel processor
	 */
	virtual std::unique_ptr<net::message::MessageChannelProcessor> BuildRoomMessageChannelProcessor(net::channel::Protocol protocol);

	/**
	 *  Build a handshake authentication context for a connection
	 *  @param	connection	The connection
	 *  @param	listener	The listener to attach to handle authentication events
	 *  @param	authContext	The context to perform authentication with on handshake
	 *  @returns	The handshake context
	 */
	core::connection::HandshakeContext BuildAuthHandshakeContext(const ServerConnectionPtr &connection,
	                                                               ConnectionMessageChannelListenerPtr listener,
	                                                               auth::AuthContextPtr authContext) const;

	auth::AuthContextPtr m_defaultRoomAuthContext;
	auth::AuthContextPtr m_defaultMasterAuthContext;
	node::NodeAuthContextFactoryPtr m_defaultNodeAuthContextFactory;
	std::vector<ServerConnectionWeakPtr> m_connections;
	std::unique_ptr<core::connection::ReconnectableMessageChannelProcessor> m_masterProcessor;
	std::map<net::channel::Protocol, std::unique_ptr<net::message::MessageChannelProcessor>> m_roomProcessors;
};

} } } }
