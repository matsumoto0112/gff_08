#pragma once

#include <strix/client/ingame/network/ServerConnection.h>
#include <strix/client/ingame/network/StrixNetworkEvents.h>

#include <strix/client/core/util/Delegates.h>

#include <memory>
#include <functional>
#include "strix/client/core/model/manager/filter/Condition.h"
#include "strix/client/core/request/RequestResult.h"
#include "strix/client/core/message/GetCountResponse.h"

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {
class Condition;
class Order;
typedef std::shared_ptr<Condition> ConditionPtr;
typedef std::shared_ptr<Order> OrderPtr;
} } } } } }

namespace strix { namespace client { namespace core { namespace request {
class RequestConfig;
typedef std::shared_ptr<RequestConfig> RequestConfigPtr;
} } } }

namespace strix { namespace client { namespace match {
class CustomizableMatchNodeClient;
typedef std::shared_ptr<CustomizableMatchNodeClient> CustomizableMatchNodeClientPtr;
} } }

namespace strix { namespace client { namespace match { namespace node { namespace model {
class CustomizableMatchServerNode;
typedef std::shared_ptr<CustomizableMatchServerNode> CustomizableMatchServerNodePtr;
} } } } }

namespace strix { namespace client { namespace node { namespace message {
class NodeRoomSearchResponse;
typedef std::shared_ptr<NodeRoomSearchResponse> NodeRoomSearchResponsePtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace auth {
class AuthContext;
typedef std::shared_ptr<AuthContext> AuthContextPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace network { namespace node {
class NodeAuthContextFactory;
class NodeSelectionStrategy;
typedef std::shared_ptr<NodeSelectionStrategy> NodeSelectionStrategyPtr;
typedef std::shared_ptr<NodeAuthContextFactory> NodeAuthContextFactoryPtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace network { namespace data {
class NodeRoomInfo;
class RoomMemberProperties;
typedef std::shared_ptr<RoomMemberProperties> RoomMemberPropertiesPtr;
typedef std::shared_ptr<NodeRoomInfo> NodeRoomInfoPtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace network {

class StrixClient;
class RoomServerConnection;
typedef std::shared_ptr<RoomServerConnection> RoomServerConnectionPtr;

/**
 *  A ServerConnection to a Strix Master Server
 *
 *  Provides methods for connecting to nodes and searching and joining nodes from the master server 
 */
class MasterServerConnection : public ServerConnection, public std::enable_shared_from_this<MasterServerConnection>
{
public:
	MasterServerConnection(std::weak_ptr<StrixClient> strixClient);

	/**
	 *  Setup the connection with the given message channel and protocol
	 *  @param	messageChannel	The channel this connection is on
	 *  @param	protocol	The protocol to use
	 */
	void Init(net::message::MessageChannelPtr messageChannel, net::channel::Protocol protocol) override;

	/**
	 *  Called when the underlying message channel closes
	 */
	void OnChannelClose() override;

	/**
	 *  Called when the underlying message channel has an error
	 */
	void OnChannelError(int errorCode) override;

	/**
	 *  Disconnect the connection
	 */
	void Disconnect() override;

	/**
	 *  Get the node selection strategy for this connection
	 *  @returns	The node selection strategy
	 */
	node::NodeSelectionStrategyPtr GetNodeSelectionStrategy() const;

	/**
	 *  Set the node selection strategy for this connection
	 *  @param	nodeSelectionStrategy	The strategy
	 */
	void SetNodeSelectionStrategy(node::NodeSelectionStrategyPtr nodeSelectionStrategy);

	/**
	 *  Get the node authentication context factory for this connection
	 *  @returns	The factory
	 */
	node::NodeAuthContextFactoryPtr GetNodeAuthContextFactory() const;

	/**
	 *  Set the node authentication context factory for this connection
	 *  @param	nodeAuthContextFactory	The factory
	 */
	void SetNodeAuthContextFactory(node::NodeAuthContextFactoryPtr nodeAuthContextFactory);

	/**
	 *  Connect to a room server. Callbacks are called on success/failure
	 *  @param	successHandler	Called on successful connection. A function that takes RoomServerConnectEventArgs as input
	 *  @param	failureHandler	Called on a failed connection attempt. A function that takes ServerConnectFailedEventArgs as input
	 *  @param	authContext	An optional authentication context for if the connection attempt requires authentication
	 */
	void ConnectToRoomServer(RoomServerConnectEventHandler successHandler, ServerConnectFailedEventHandler failureHandler,
		auth::AuthContextPtr authContext = nullptr);

	/**
	 *  Connect to a room server. Callbacks are called on success/failure
	 *  @param	node	The node to connect to 
	 *  @param	successHandler	Called on successful connection. A function that takes RoomServerConnectEventArgs as input
	 *  @param	failureHandler	Called on a failed connection attempt. A function that takes ServerConnectFailedEventArgs as input
	 *  @param	authContext	An optional authentication context for if the connection attempt requires authentication
	 */
	void ConnectToRoomServer(client::match::node::model::CustomizableMatchServerNodePtr node, RoomServerConnectEventHandler successHandler,
		ServerConnectFailedEventHandler failureHandler, auth::AuthContextPtr authContext = nullptr);

	/**
	 *  Search for nodes (servers). Callbacks are called on success/failure
	 *  @param	limit	The maximum number of nodes to return
	 *  @param	offset	The offset into all found nodes from which to return. If 40 nodes are found, the limit is 20, and this value is 10, nodes 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes NodeSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes MasterServerConnectionFailureEventArgs as input
	 *  @param	config	Optional parameters for the request
	 */
	virtual void SearchNode(int limit, int offset,
		NodeSearchEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for nodes (servers) with a given condition. Callbacks are called on success/failure
	 *  @param	condition	The condition to match against
	 *  @param	limit	The maximum number of nodes to return
	 *  @param	offset	The offset into all found nodes from which to return. If 40 nodes are found, the limit is 20, and this value is 10, nodes 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes NodeSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes MasterServerConnectionFailureEventArgs as input
	 *  @param	config	Optional parameters for the request
	 */
	virtual void SearchNode(core::model::manager::filter::ConditionPtr condition, int limit, int offset,
		NodeSearchEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for nodes (servers) with a given condition and return in a given order. Callbacks are called on success/failure
	 *  @param	condition	The condition to match against
	 *  @param	order	The order to return results in
	 *  @param	limit	The maximum number of nodes to return
	 *  @param	offset	The offset into all found nodes from which to return. If 40 nodes are found, the limit is 20, and this value is 10, nodes 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes NodeSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes MasterServerConnectionFailureEventArgs as input
	 *  @param	config	Optional parameters for the request
	 */
	virtual void SearchNode(core::model::manager::filter::ConditionPtr condition, core::model::manager::filter::OrderPtr order, int limit, int offset,
		NodeSearchEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for rooms on nodes from the master server. Callbacks are called on success/failure
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes NodeRoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes MasterServerConnectionFailureEventArgs as input
	 *  @param	config	Optional parameters for the request
	 */
	virtual void SearchNodeRoom(int limit, int offset,
		NodeRoomSearchEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for rooms on nodes from the master server with some condition. Callbacks are called on success/failure
	 *  @param	condition	The condition to match against
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes NodeRoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes MasterServerConnectionFailureEventArgs as input
	 *  @param	config	Optional parameters for the request
	 */
	virtual void SearchNodeRoom(core::model::manager::filter::ConditionPtr condition, int limit, int offset,
		NodeRoomSearchEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for rooms on nodes from the master server with some condition and return results in some order. Callbacks are called on success/failure
	 *  @param	condition	The condition to match against
	 *  @param	order	The order to return results in
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes NodeRoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes MasterServerConnectionFailureEventArgs as input
	 *  @param	config	Optional parameters for the request
	 */
	virtual void SearchNodeRoom(core::model::manager::filter::ConditionPtr condition, core::model::manager::filter::OrderPtr order, int limit, int offset,
		NodeRoomSearchEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for rooms on nodes from the master server and return only joinable rooms. Callbacks are called on success/failure
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes NodeRoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes MasterServerConnectionFailureEventArgs as input
	 *  @param	config	Optional parameters for the request
	 */
	virtual void SearchJoinableNodeRoom(int limit, int offset,
		NodeRoomSearchEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Search for rooms on nodes from the master server with some condition and return results in some order, and return only joinable rooms. Callbacks are called on success/failure
	 *  @param	condition	The condition to match against
	 *  @param	order	The order to return results in
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes NodeRoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes MasterServerConnectionFailureEventArgs as input
	 *  @param	config	Optional parameters for the request
	 */
	virtual void SearchJoinableNodeRoom(core::model::manager::filter::ConditionPtr condition, core::model::manager::filter::OrderPtr order, int limit, int offset,
		NodeRoomSearchEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on a room server from the master server. Callbacks are called on success/failure
	 *  @param	playerName	The joining player's name
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	connectHandler	Called on a successful room server connection. A function that takes RoomServerConnectionEventArgs as input
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes MasterServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomNodeRoom(std::string playerName, bool pauseNetworkObjects, RoomServerConnectEventHandler connectHandler, RoomContextOpenEventHandler handler,
		MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on a room server from the master server. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	connectHandler	Called on a successful room server connection. A function that takes RoomServerConnectionEventArgs as input
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes MasterServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomNodeRoom(data::RoomMemberPropertiesPtr memberProperties, bool pauseNetworkObjects, RoomServerConnectEventHandler connectHandler,
		RoomContextOpenEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on a room server from the master server. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	connectHandler	Called on a successful room server connection. A function that takes RoomServerConnectionEventArgs as input
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes MasterServerConnectionFailureArgs as input
	 *  @param	authContext	An authentication context to use to connect to the room servers when searching for the room
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomNodeRoom(data::RoomMemberPropertiesPtr memberProperties, bool pauseNetworkObjects, RoomServerConnectEventHandler connectHandler, RoomContextOpenEventHandler handler,
		MasterServerConnectionFailureEventHandler failureHandler, auth::AuthContextPtr authContext = nullptr, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on a room server from the master server. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	connectHandler	Called on a successful room server connection. A function that takes RoomServerConnectionEventArgs as input
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes MasterServerConnectionFailureArgs as input
	 *  @param	authContext	An authentication context to use to connect to the room servers when searching for the room
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomNodeRoom(std::map<std::string, strix::net::object::ObjectPtr> memberProperties, bool pauseNetworkObjects, RoomServerConnectEventHandler connectHandler,
		RoomContextOpenEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler,
		auth::AuthContextPtr authContext = nullptr, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on a room server from the master server matching some condition. Callbacks are called on success/failure
	 *  @param	playerName	The joining player's name
	 *  @param	condition	The condition to match against
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	connectHandler	Called on a successful room server connection. A function that takes RoomServerConnectionEventArgs as input
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes MasterServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomNodeRoom(std::string playerName, core::model::manager::filter::ConditionPtr condition, bool pauseNetworkObjects, RoomServerConnectEventHandler connectHandler, 
	    RoomContextOpenEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on a room server from the master server matching some condition. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	condition	The condition to match against
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	connectHandler	Called on a successful room server connection. A function that takes RoomServerConnectionEventArgs as input
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes MasterServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomNodeRoom(data::RoomMemberPropertiesPtr memberProperties, core::model::manager::filter::ConditionPtr condition, bool pauseNetworkObjects, RoomServerConnectEventHandler connectHandler,
	    RoomContextOpenEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on a room server from the master server matching some condition. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	condition	The condition to match against
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	connectHandler	Called on a successful room server connection. A function that takes RoomServerConnectionEventArgs as input
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes MasterServerConnectionFailureArgs as input
	 *  @param	authContext	An authentication context to use to connect to the room servers when searching for the room
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomNodeRoom(data::RoomMemberPropertiesPtr memberProperties, core::model::manager::filter::ConditionPtr condition, bool pauseNetworkObjects, RoomServerConnectEventHandler connectHandler,
	    RoomContextOpenEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler, auth::AuthContextPtr authContext = nullptr, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on a room server from the master server matching some condition. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	condition	The condition to match against
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	connectHandler	Called on a successful room server connection. A function that takes RoomServerConnectionEventArgs as input
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes MasterServerConnectionFailureArgs as input
	 *  @param	authContext	An authentication context to use to connect to the room servers when searching for the room
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomNodeRoom(std::map<std::string, strix::net::object::ObjectPtr> memberProperties, core::model::manager::filter::ConditionPtr condition, bool pauseNetworkObjects, 
	    RoomServerConnectEventHandler connectHandler, RoomContextOpenEventHandler handler, MasterServerConnectionFailureEventHandler failureHandler,
	    auth::AuthContextPtr authContext = nullptr, core::request::RequestConfigPtr config = nullptr);

	void GetNodeCount(core::request::RequestResultHandlerT<core::message::GetCountResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr = nullptr);

	/**
	 *  Add a handler to call when the master server connection closes
	 *  @param	handler	The handler. A function that takes a MasterServerConnectionClosedEventArgs as input
	 *  @returns	The key to this handler
	 */
	core::util::DelegateList<>::Handle AddMasterServerConnectionClosedHandler(MasterServerConnectionClosedEventHandler handler);

	/**
	 *  Remove a handler from the connection closed handler list with the specified key
	 *  @param	handle	The key for the handler to remove
	 */
	void RemoveMasterServerConnectionClosedHandler(core::util::DelegateList<>::Handle handle);

protected:

	/**
	 *  Create a list of NodeRoomInfos from a search response
	 *  @param	response	The search response
	 *  @returns	The list of infos
	 */
	static std::vector<data::NodeRoomInfoPtr> MakeNodeRoomInfoList(const client::node::message::NodeRoomSearchResponsePtr &response);

	core::util::DelegateList<MasterServerConnectionClosedEventArgs> m_masterServerConnectionClosedDelegate;

private:
	std::weak_ptr<StrixClient> m_strixClient;
	node::NodeSelectionStrategyPtr m_nodeSelectionStrategy;
	node::NodeAuthContextFactoryPtr m_nodeAuthContextFactory;
	match::CustomizableMatchNodeClientPtr m_nodeClient;
};

} } } }
