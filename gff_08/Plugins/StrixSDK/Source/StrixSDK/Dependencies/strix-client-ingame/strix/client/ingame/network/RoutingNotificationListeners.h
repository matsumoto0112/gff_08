#pragma once

#include <strix/client/replica/ReplicaNotificationListener.h>
#include <strix/client/room/RoomNotificationListener.h>
#include <strix/client/match/MatchRoomNotificationListener.h>
#include "strix/client/core/util/Delegates.h"

#include <map>


namespace strix {namespace net {namespace object {
class MetaClass;
} } }

namespace strix { namespace client { namespace replica
{
class ReplicaClient;
typedef std::shared_ptr<ReplicaClient> ReplicaClientPtr;
} } }

namespace strix { namespace client { namespace ingame { namespace network {

/**
 *  Listener that routes events to the correct MatchRoomNotificationListeners
 */
class RoutingMatchRoomNotificationListener : public match::MatchRoomNotificationListener
{
public:
	RoutingMatchRoomNotificationListener(const net::object::MetaClass &roomClass);

	/**
	 *  Check if this listener has a listener for a given room
	 *  @param	roomId	The id of the room
	 *  @returns	True if a listener exists for that room
	 */
	bool HasRoutedListener(long long roomId);

	/**
	 *  Add a listener for a specific room
	 *  @param	roomId	The ID of the room to listen for
	 *  @param	listener	The listener
	 */
	void AddRoutedListener(long long roomId, match::MatchRoomNotificationListenerPtr listener);

	/**
	 *  Remove the listener for the room
	 *  @param	roomId	The ID of the room to remove the listener of
	 */
	void RemoveRoutedListener(long long roomId);

	/**
	 *  Called on a kick notification. Routes the notification to the correct listener
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnMatchRoomKickNotification(strix::net::message::MessageChannelPtr messageChannel, 
		match::room::message::MatchRoomKickNotificationPtr msg) override;
private:
	std::map<long long, match::MatchRoomNotificationListenerPtr> m_listenersByRoomId;
};

/**
 *  Listener that routes events to the correct RoomNotificationListeners
 */
class RoutingRoomNotificationListener : public room::RoomNotificationListener
{
public:
	RoutingRoomNotificationListener(const net::object::MetaClass &roomClass, const net::object::MetaClass &memberClass);
	
	/**
	 *  Check if this listener has a listener for a given room
	 *  @param	roomId	The id of the room
	 *  @returns	True if a listener exists for that room
	 */
	bool HasRoutedListener(long long roomId);

	/**
	 *  Add a listener for a specific room
	 *  @param	roomId	The ID of the room to listen for
	 *  @param	listener	The listener
	 */
	void AddRoutedListener(long long roomId, room::RoomNotificationListenerPtr listener);

	/**
	 *  Remove the listener for the room
	 *  @param	roomId	The ID of the room to remove the listener of
	 */
	void RemoveRoutedListener(long long roomId);

	/**
	 *  Called on a room join notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnRoomJoinNotification(strix::net::message::MessageChannelPtr messageChannel,
		room::message::RoomJoinNotificationPtr msg) override;

	/**
	 *  Called on a room leave notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnRoomLeaveNotification(strix::net::message::MessageChannelPtr messageChannel,
		room::message::RoomLeaveNotificationPtr msg) override;

	/**
	 *  Called on a room delete notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnRoomDeleteNotification(strix::net::message::MessageChannelPtr messageChannel,
		room::message::RoomDeleteNotificationPtr msg) override;

	/**
	 *  Called on a room set notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnRoomSetNotification(strix::net::message::MessageChannelPtr messageChannel,
		room::message::RoomSetNotificationPtr msg) override;

	/**
	 *  Called on a room set member notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnRoomSetMemberNotification(strix::net::message::MessageChannelPtr messageChannel,
		room::message::RoomSetMemberNotificationPtr msg) override;

	/**
	 *  Called on a room relay notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnRoomRelayNotification(strix::net::message::MessageChannelPtr messageChannel,
		room::message::RoomRelayNotificationPtr msg) override;

	/**
	 *  Called on a room direct relay notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnRoomDirectRelayNotification(strix::net::message::MessageChannelPtr messageChannel,
		room::message::RoomDirectRelayNotificationPtr msg) override;
private:
	std::map<long long, room::RoomNotificationListenerPtr> m_listenersByRoomId;
};


/**
 *  Listener that routes events to the correct ReplicaNotificationListeners
 */
class RoutingReplicaNotificationListener : public replica::ReplicaNotificationListener
{
public:
	RoutingReplicaNotificationListener(const net::object::MetaClass &replicaClass);
	
	/**
	 *  Check if this listener has a listener for a given room
	 *  @param	roomId	The id of the room
	 *  @returns	True if a listener exists for that room
	 */
	bool HasRoutedListener(long long roomId);

	/**
	 *  Add a listener for a specific room
	 *  @param	roomId	The ID of the room to listen for
	 *  @param	listener	The listener
	 */
	void AddRoutedListener(long long roomId, replica::ReplicaNotificationListenerPtr listener);

	/**
	 *  Remove the listener for the room
	 *  @param	roomId	The ID of the room to remove the listener of
	 */
	void RemoveRoutedListener(long long roomId);

	/**
	 *  Register update handle with replica client for create responses
	 *  @param	client	The replica client to register with
	 */
	core::util::DelegateList<>::Handle RegisterReplicaCreateHandle(replica::ReplicaClientPtr client);

	/**
	 *  Register update handle with replica client for delete responses
	 *  @param	client	The replica client to register with
	 */
	core::util::DelegateList<>::Handle RegisterReplicaDeleteHandle(replica::ReplicaClientPtr client);

	/**
	 *  Called on a replica create notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnReplicaCreateNotification(strix::net::message::MessageChannelPtr messageChannel,
		replica::message::ReplicaCreateNotificationPtr msg) override;

	/**
	 *  Called on a replica set notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnReplicaSetNotification(strix::net::message::MessageChannelPtr messageChannel,
		replica::message::ReplicaSetNotificationPtr msg) override;

	/**
	 *  Called on a replica delete notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnReplicaDeleteNotification(strix::net::message::MessageChannelPtr messageChannel,
		replica::message::ReplicaDeleteNotificationPtr msg) override;

	/**
	 *  Called on a replica change owner notification. Routes the notification to the correct room
	 *  @param	messageChannel	The message channel the notification was received on
	 *  @param	msg	The notification message
	 */
	void OnReplicaChangeOwnerNotification(strix::net::message::MessageChannelPtr messageChannel,
		replica::message::ReplicaChangeOwnerNotificationPtr msg) override;
	/**
	 *  Update the map of room ids with the given information
	 *  @param	replicaId	The replica ID to update
	 *  @param	roomId	The room ID
	 */
	void OnReplicaCreateResponse(long long replicaId, long long roomId);

	/**
	 *  Delete the given replica from the room map
	 *  @param	replicaId	The replica ID to remove
	 */
	void OnReplicaDeleteResponse(long long replicaId);

protected:

	std::map<long long, replica::ReplicaNotificationListenerPtr> m_listenersByRoomId;
	std::map<long long, long long> m_roomIdByReplicaId;
};

} } } }
