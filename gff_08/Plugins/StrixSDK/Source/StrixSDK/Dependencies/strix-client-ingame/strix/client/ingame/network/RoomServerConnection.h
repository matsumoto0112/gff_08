#pragma once

#include <strix/client/ingame/network/ServerConnection.h>
#include <strix/client/ingame/network/RoutingNotificationListeners.h>
#include <strix/client/ingame/network/StrixNetworkEvents.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/util/Delegates.h>

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
class CustomizableMatchRoomClient;
typedef std::shared_ptr<CustomizableMatchRoomClient> CustomizableMatchRoomClientPtr;
} } }

namespace strix { namespace client { namespace ingame { namespace network { namespace data {
class RoomMemberProperties;
typedef std::shared_ptr<RoomMemberProperties> RoomMemberPropertiesPtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace network {

class RoomContext;
typedef std::weak_ptr<RoomContext> RoomContextWeakPtr;

/**
 *  A ServerConnection to a Strix Room Server
 *  
 *  Controls join, create, and search operations on a room server through it's room client
 */
class RoomServerConnection : public ServerConnection, public std::enable_shared_from_this<RoomServerConnection>
{
public:
	RoomServerConnection();
	~RoomServerConnection();

	/**
	 *  Setup the connection with the given message channel and protocol
	 *  @param	messageChannel	The channel this connection is on
	 *  @param	protocol	The protocol to use
	 */
	void Init(net::message::MessageChannelPtr messageChannel, net::channel::Protocol protocol) override;

	/**
	 *  Process the connection
	 */
	void Process() override;

	/**
	 *  Called when the underlying message channel closes
	 */
	void OnChannelClose() override;

	/**
	 *  Disconnect the connection
	 */
	void Disconnect() override;

	/**
	 *  Request to join a room. Callbacks are called on success/failure
	 *  @param	roomId	The room id to join
	 *  @param	memberProperties	The joining room member's properties
	 *  @param	password	The room's password
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRoom(long long roomId, std::map<std::string, strix::net::object::ObjectPtr> memberProperties, std::string password,
		          bool pauseNetworkObjects, RoomContextOpenEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler,
		          core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to create a room. Will automatically join a member after creation. Callbacks are called on success/failure
	 *  @param	roomProperties	The properties the new room should have
	 *  @param	memberProperties	The initial joining room member's properties
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	handler	Called on successful create. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed create. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void CreateRoom(std::map<std::string, strix::net::object::ObjectPtr> roomProperties, std::map<std::string, strix::net::object::
	                ObjectPtr> memberProperties, bool pauseNetworkObjects, RoomContextOpenEventHandler handler,
		            RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to search for rooms with no condition or order. Callbacks are called on success/failure
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes RoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void SearchRoom(int limit, int offset,
	                        RoomSearchEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Requests to search for rooms with a given condition. Callbacks are called on success/failure
	 *  @param	condition	The condition to match rooms against
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes RoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void SearchRoom(core::model::manager::filter::ConditionPtr condition, int limit, int offset,
	                        RoomSearchEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to search for rooms with a given condition and return in a given order. Callbacks are called on success/failure
	 *  @param	condition	The condition to match rooms against
	 *  @param	order	The order to return the results in
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes RoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void SearchRoom(core::model::manager::filter::ConditionPtr condition, core::model::manager::filter::OrderPtr order, int limit, int offset,
	                        RoomSearchEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to search for rooms. Returns only joinable rooms. Callbacks are called on success/failure
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes RoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void SearchJoinableRoom(int limit, int offset,
	                                RoomSearchEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to search for rooms with a given condition and return in a given order. Returns only joinable rooms. Callbacks are called on success/failure
	 *  @param	condition	The condition to match rooms against
	 *  @param	order	The order to return the results in
	 *  @param	limit	The maximum number of rooms to return
	 *  @param	offset	The offset into all found rooms from which to return. If 40 rooms are found, the limit is 20, and this value is 10, rooms 10-30 will be returned
	 *  @param	handler	Called on successful search. A function that takes RoomSearchEventArgs as input
	 *  @param	failureHandler	Called on failed search. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void SearchJoinableRoom(core::model::manager::filter::ConditionPtr condition, core::model::manager::filter::OrderPtr order, int limit, int offset,
	                                RoomSearchEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on the server. Callbacks are called on success/failure
	 *  @param	playerName	The joining player's name
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomRoom(std::string playerName, bool pauseNetworkObjects, RoomContextOpenEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler,
	                    core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on the server. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomRoom(std::map<std::string, strix::net::object::ObjectPtr> memberProperties, bool pauseNetworkObjects, RoomContextOpenEventHandler handler,
	                    RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on the server. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomRoom(data::RoomMemberPropertiesPtr memberProperties, bool pauseNetworkObjects, RoomContextOpenEventHandler handler,
		RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on the server matching the given condition. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	condition	The condition to match against
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomRoom(std::map<std::string, strix::net::object::ObjectPtr> memberProperties, core::model::manager::filter::ConditionPtr condition,
				       bool pauseNetworkObjects, RoomContextOpenEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on the server matching the given condition. Callbacks are called on success/failure
	 *  @param	memberProperties	The joining player's properties
	 *  @param	condition	The condition to match against
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomRoom(data::RoomMemberPropertiesPtr memberProperties, core::model::manager::filter::ConditionPtr condition, bool pauseNetworkObjects, 
					RoomContextOpenEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Join a random room on the server matching the given condition. Callbacks are called on success/failure
	 *  @param	playerName	The joining player's name
	 *  @param	condition	The condition to match against
	 *  @param	pauseNetworkObjects	If true, after join the room's network objects will be in the paused state
	 *  @param	handler	Called on successful join. A function that takes RoomContextOpenEventArgs as input
	 *  @param	failureHandler	Called on failed join. A function that takes RoomServerConnectionFailureArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void JoinRandomRoom(std::string playerName, core::model::manager::filter::ConditionPtr condition, bool pauseNetworkObjects,
					RoomContextOpenEventHandler handler, RoomServerConnectionFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Add a handler to be called when this connection closes
	 *  @param	handler	The handler to add. A function that takes RoomServerConnectionClosedEventArgs as input
	 *  @returns	The key to the handler
	 */
	core::util::DelegateList<>::Handle AddRoomServerConnectionClosedHandler(RoomServerConnectionClosedEventHandler handler);

	/**
	 *  Remove the handle with the given key from the list of connection closed handlers
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomServerConnectionClosedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Get the routing match room notification listener for this connection
	 *  @returns	The listener
	 */
	RoutingMatchRoomNotificationListener &GetRoutingMatchRoomNotificationListener();

	/**
	 *  Get the routing room notification listener for this connection
	 *  @returns	The listener
	 */
	RoutingRoomNotificationListener &GetRoutingRoomNotificationListener();

	/**
	 *  Get the routing replica notification listener for this connection
	 *  @returns	The listener
	 */
	RoutingReplicaNotificationListener &GetRoutingReplicaNotificationListener();
protected:
	match::CustomizableMatchRoomClientPtr m_roomClient;
	RoutingMatchRoomNotificationListener m_matchRoomNotificationListener;
	RoutingRoomNotificationListener m_roomNotificationListener;
	RoutingReplicaNotificationListener m_replicaNotificationListener;

	std::vector<RoomContextWeakPtr> m_roomContexts;
	std::vector<RoomContextPtr> m_roomContextWaitingList;

	core::util::DelegateList<RoomServerConnectionClosedEventArgs> m_roomServerConnectionClosedDelegate;
};

} } } }
