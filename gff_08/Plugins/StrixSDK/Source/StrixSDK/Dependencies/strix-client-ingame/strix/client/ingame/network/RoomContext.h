#pragma once

#include <strix/net/object/WrapperObject.h>

#include <strix/client/room/RoomEvents.h>
#include <strix/client/core/NotificationEventArgs.h>

#include <memory>
#include <strix/client/core/util/Delegates.h>
#include <strix/client/ingame/network/StrixNetworkEvents.h>

namespace strix { namespace client { namespace core {
class UID;
typedef std::shared_ptr<UID> UIDPtr;
} } }

namespace strix { namespace client { namespace core { namespace request {
class RequestConfig;
typedef std::shared_ptr<RequestConfig> RequestConfigPtr;
} } } }

namespace strix { namespace client { namespace core { namespace time {
class SyncTimeClient;
typedef std::shared_ptr<SyncTimeClient> SyncTimeClientPtr;
} } } }

namespace strix { namespace client { namespace match {
class MatchRoomClient;
class MatchRoomData;
typedef std::shared_ptr<MatchRoomClient> MatchRoomClientPtr;
typedef std::shared_ptr<MatchRoomData> MatchRoomDataPtr;
} } }

namespace strix { namespace client { namespace match { namespace room { namespace message {
class MatchRoomKickNotification;
typedef std::shared_ptr<MatchRoomKickNotification> MatchRoomKickNotificationPtr;
} } } } }

namespace strix { namespace client { namespace replica {
class ReplicaClient;
typedef std::shared_ptr<ReplicaClient> ReplicaClientPtr;
} } }

namespace strix { namespace client { namespace room { namespace message {
class RoomRelayMessage;
class RoomDirectRelayMessage;
typedef std::shared_ptr<RoomRelayMessage> RoomRelayMessagePtr;
typedef std::shared_ptr<RoomDirectRelayMessage> RoomDirectRelayMessagePtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace network { namespace data {
class RoomProperties;
class RoomMemberProperties;
typedef std::shared_ptr<RoomProperties> RoomPropertiesPtr;
typedef std::shared_ptr<RoomMemberProperties> RoomMemberPropertiesPtr;
} } } } }

namespace strix { namespace client { namespace ingame { namespace object {
class NetworkObjectManager;
typedef std::shared_ptr<NetworkObjectManager> NetworkObjectManagerPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace rpc {
class RpcManager;
typedef std::shared_ptr<RpcManager> RpcManagerPtr;
} } } }

namespace strix { namespace client { namespace ingame { namespace network {

class RoomServerConnection;
typedef std::shared_ptr<RoomServerConnection> RoomServerConnectionPtr;

/**
 *  Context information of a room for a member, with methods for 
 *  performing operations on it
 */
class RoomContext : public std::enable_shared_from_this<RoomContext>
{
public:
	RoomContext(RoomServerConnectionPtr connection, bool notificationsPaused);
	virtual ~RoomContext();

	/**
	 *  Check if this context has valid room data
	 *  @returns	True if valid
	 */
	bool IsValid();

	/**
	 *  Check if this member is the owner of this room
	 *  @returns	True if the member is the owner
	 */
	bool IsRoomOwner();

	/**
	 *  Get this room's id
	 *  @returns	The id of the room
	 */
	long long GetRoomId() const;

	/**
	 *  Get the room data
	 *  @returns	The room data
	 */
	match::MatchRoomDataPtr GetRoomData() const;

	/**
	 *  Get the current room server connection connecting the member to this room
	 *  @returns	The room server connection
	 */
	std::weak_ptr<RoomServerConnection> GetConnection() const;

	/**
	 *  Process pending operations on this room context
	 */
	void Process();

	/**
	 *  Called when the underlying message channel closes
	 */
	void OnChannelClose();

	/**
	 *  Leave the room. Callbacks are called on success/failure
	 *  @param	handler	Called on a successful leave. A function that takes a RoomLeaveEventArgs as input
	 *  @param	failureHandler	Called on a failed leave. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void Leave(RoomLeaveEventHandler handler, RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Delete the room. Callbacks are called on success/failure
	 *  @param	handler	Called on a successful delete. A function that takes a RoomDeleteEventArgs as input
	 *  @param	failureHandler	Called on a failed delete. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void DeleteRoom(RoomDeleteEventHandler handler, RoomContextFailureEventHandler failureHandler,	core::request::RequestConfigPtr config = nullptr);

	// ToDo: remove room id (unnecessary)?
	/**
	 *  Set the room properties. Callbacks are called on success/failure
	 *  @param	roomId	The id of the room
	 *  @param	roomProperties	The room properties to set
	 *  @param	handler	Called on a successful set. A function that takes a RoomSetEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SetRoom(long long roomId, data::RoomPropertiesPtr roomProperties, RoomSetEventHandler handler,
		RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	// ToDo: remove room id (unnecessary)?
	/**
	 *  Set the room properties. Callbacks are called on success/failure
	 *  @param	roomId	The id of the room
	 *  @param	roomProperties	The room properties to set
	 *  @param	handler	Called on a successful set. A function that takes a RoomSetEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SetRoom(long long roomId, std::map<std::string, strix::net::object::ObjectPtr> roomProperties, RoomSetEventHandler handler,
	             RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the room properties. Callbacks are called on success/failure
	 *  @param	roomProperties	The room properties to set
	 *  @param	handler	Called on a successful set. A function that takes a RoomSetEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SetRoom(data::RoomPropertiesPtr roomProperties, RoomSetEventHandler handler,
		RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the room properties. Callbacks are called on success/failure
	 *  @param	roomProperties	The room properties to set
	 *  @param	handler	Called on a successful set. A function that takes a RoomSetEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SetRoom(std::map<std::string, strix::net::object::ObjectPtr> roomProperties, RoomSetEventHandler handler,
		RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the properties on a room member. Callbacks are called on success/failure
	 *  @param	memberId	The id of the member
	 *  @param	memberProperties	The member properties to set
	 *  @param	handler	Called on a successful set. A function that takes a RoomMemberSetEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SetRoomMember(long long memberId, data::RoomMemberPropertiesPtr memberProperties, RoomMemberSetEventHandler handler,
		RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the properties on a room member. Callbacks are called on success/failure
	 *  @param	memberId	The id of the member
	 *  @param	memberProperties	The member properties to set
	 *  @param	handler	Called on a successful set. A function that takes a RoomMemberSetEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SetRoomMember(long long memberId, std::map<std::string, strix::net::object::ObjectPtr> memberProperties, 
		RoomMemberSetEventHandler handler, RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the properties on a room member. Callbacks are called on success/failure
	 *  @param	memberProperties	The member properties to set
	 *  @param	handler	Called on a successful set. A function that takes a RoomMemberSetEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SetRoomMember(data::RoomMemberPropertiesPtr memberProperties, RoomMemberSetEventHandler handler,
		RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the properties on a room member. Callbacks are called on success/failure
	 *  @param	memberProperties	The member properties to set
	 *  @param	handler	Called on a successful set. A function that takes a RoomMemberSetEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SetRoomMember(std::map<std::string, strix::net::object::ObjectPtr> memberProperties, RoomMemberSetEventHandler handler,
	                   RoomContextFailureEventHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Send a relay message to the room. Callbacks are called on success/failure
	 *  @param	messageToRelay	The relay message to send
	 *  @param	handler	Called on a successful set. A function that takes a RoomRelayEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SendRoomRelay(net::object::ObjectPtr messageToRelay, RoomRelayEventHandler handler = nullptr,
		RoomContextFailureEventHandler failureHandler = nullptr, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Send a relay message to the room. Callbacks are called on success/failure
	 *  @param	message	The relay message to send
	 *  @param	handler	Called on a successful set. A function that takes a RoomRelayEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SendRoomRelay(room::message::RoomRelayMessagePtr message, RoomRelayEventHandler handler = nullptr,
		RoomContextFailureEventHandler failureHandler = nullptr, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Send a relay message to a member in the room. Callbacks are called on success/failure
	 *  @param	to	The UID of the member to send to
	 *  @param	messageToRelay	The relay message to send
	 *  @param	handler	Called on a successful set. A function that takes a RoomRelayEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SendRoomDirectRelay(core::UIDPtr to, net::object::ObjectPtr messageToRelay, RoomDirectRelayEventHandler handler = nullptr,
		RoomContextFailureEventHandler failureHandler = nullptr, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Send a relay message to a member in the room. Callbacks are called on success/failure
	 *  @param	message	The relay message to send
	 *  @param	handler	Called on a successful set. A function that takes a RoomRelayEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void SendRoomDirectRelay(room::message::RoomDirectRelayMessagePtr message, RoomDirectRelayEventHandler handler = nullptr,
		RoomContextFailureEventHandler failureHandler = nullptr, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Kick a room member from the room. Callbacks are called on success/failure
	 *  @param	kickedPlayerUid	The UID of the player to kick
	 *  @param	handler	Called on a successful set. A function that takes a RoomMemberKickEventArgs as input
	 *  @param	failureHandler	Called on a failed set. A function that takes a RoomContextFailureEventArgs as input
	 *  @param	config	Additional parameters for the request
	 */
	void KickRoomMember(core::UIDPtr kickedPlayerUid, RoomMemberKickEventHandler handler = nullptr,
		RoomContextFailureEventHandler failureHandler = nullptr, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Add a handler to call when the room context becomes invalid
	 *  @param	handler	The handler to add. A function that takes a RoomContextInvalidateEventArgs as input
	 *  @returns	The key to the handler
	 */
	core::util::DelegateList<>::Handle AddRoomContextInvalidateHandler(RoomContextInvalidateEventHandler handler);

	/**
	 *  Remove the handler with the given key from the list of room context invalidation handlers
	 *  @param	handle	The key to the handler
	 */
	void RemoveRoomContextInvalidateHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Get the match room client used by this context
	 *  @returns	The client
	 */
	match::MatchRoomClientPtr GetMatchRoomClient() const;

	/**
	 *  Get the synchronization client used by this context
	 *  @returns	The client
	 */
	core::time::SyncTimeClientPtr GetSyncTimeClient() const;

	/**
	 *  Get the replica client used by this context
	 *  @returns	The client
	 */
	replica::ReplicaClientPtr GetReplicaClient() const;

	/**
	 *  Get the network object manager used by this context
	 *  @returns	The NOM
	 */
	object::NetworkObjectManagerPtr GetNetworkObjectManager() const;

	/**
	 *  Get the RPC manager used by this context
	 *  @returns	The RPC manager
	 */
	rpc::RpcManagerPtr GetRpcManager() const;

protected:

	/**
	 *  Called when the room is joined by the member
	 *  @param	args	The joined event information
	 */
	void OnRoomJoined(room::RoomJoinedEventArgs args);

	/**
	 *  Called when the room is created by the member
	 *  @param	args	The created event information
	 */
	void OnRoomCreated(room::RoomCreatedEventArgs args);

	/**
	 *  Called when the room is deleted by the member
	 *  @param	args	The deleted event information
	 */
	void OnRoomDeleted(room::RoomDeletedEventArgs args);

	/**
	 *  Called when the room is left by the member
	 *  @param	args	The left event information
	 */
	void OnRoomLeft(room::RoomLeftEventArgs args);

	/**
	 *  Called when the member is notified they have been kicked
	 *  @param	args	The kick notification information
	 */
	void OnRoomKickNotified(core::NotificationEventArgs<match::room::message::MatchRoomKickNotificationPtr> args);

	/**
	 *  Called when the member is notified the room has been deleted
	 *  @param	args	The deleted notification information
	 */
	void OnRoomDeleteNotified(core::NotificationEventArgs<room::message::RoomDeleteNotificationPtr> args);

	/**
	 *  Called when the room has been invalidated due to some action such as the room being deleted, or the member being kicked
	 */
	void OnInvalidate();
	
	core::util::DelegateList<RoomContextInvalidateEventArgs> m_roomContextInvalidateDelegate;

private:
	void BeginNotificationListening();
	void StopNotificationListening();

	void RegisterClientEventHandlers();
	void UnregisterClientEventHandlers();

	long long m_routingRoomId;

	std::weak_ptr<RoomServerConnection> m_roomServerConnection;
	net::message::MessageChannelPtr m_messageChannel;
	core::time::SyncTimeClientPtr m_syncTimeClient;
	match::MatchRoomClientPtr m_matchRoomClient;
	replica::ReplicaClientPtr m_replicaClient;
	rpc::RpcManagerPtr m_rpcManager;
	object::NetworkObjectManagerPtr m_networkObjectManager;

	core::util::DelegateList<>::Handle m_onRoomJoinedHandle;
	core::util::DelegateList<>::Handle m_onRoomCreatedHandle;
	core::util::DelegateList<>::Handle m_onRoomDeletedHandle;
	core::util::DelegateList<>::Handle m_onRoomLeftHandle;
	core::util::DelegateList<>::Handle m_onRoomDeleteNotifiedHandle;
	core::util::DelegateList<>::Handle m_onRoomKickNotifiedHandle;

	/* The handle for the on replica create response */
	core::util::DelegateList<>::Handle m_replicaCreateResponseHandle;

	/* The handle for the on replica delete response */
	core::util::DelegateList<>::Handle m_replicaDeleteResponseHandle;
};

typedef std::shared_ptr<RoomContext> RoomContextPtr;
typedef std::weak_ptr<RoomContext> RoomContextWeakPtr;

} } } }
