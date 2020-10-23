#pragma once

#include <strix/client/room/RoomClient.h>
#include <strix/client/match/MatchMessages.h>
#include <strix/client/match/MatchRoomData.h>

namespace strix { namespace client { namespace match {

class MatchRoomNotificationListener;
typedef std::shared_ptr<MatchRoomNotificationListener> MatchRoomNotificationListenerPtr;

typedef std::function<void(core::NotificationEventArgs<room::message::MatchRoomKickNotificationPtr>)> MatchRoomKickNotificationEventHandler;

/**
 *  Controller class for functions on Match Rooms
 *  Extends the RoomClient class to add functionality for rooms with matches
 */
class MatchRoomClient : public strix::client::room::RoomClient
{
public:
	MatchRoomClient(const net::object::MetaClass &roomClass, const net::object::MetaClass &roomMemberClass);
	MatchRoomClient(MatchRoomDataPtr roomData, const net::object::MetaClass &roomClass, const net::object::MetaClass &roomMemberClass);

	virtual ~MatchRoomClient();

	/**
	 *  Add the dispatcher. Attaches this client's listener's message handlers to the dispatcher
	 *  @param	messageDispatcher	The dispatcher containing the message handlers
	 */
	void AddMessageHandlers(const core::message::DefaultParameterMessageDispatcherPtr &messageDispatcher) override;

	/**
	 *  Remove message handlers
	 */
	void RemoveMessageHandlers() override;

	/**
	 *  Get the notification listener for this client
	 *  @returns	The match room notification listener
	 */
	MatchRoomNotificationListenerPtr GetMatchRoomNotificationListener();

	using strix::client::room::RoomClient::Create;

	/**
	 *  Request creation of a room with the given properties. The callbacks are triggered on a response from the server
	 *  @param	properties	A map of strings (property names) and objects (values) for the room properties
	 *  @param	playerName	The name of the creating player, who will become the initial owner of the room
	 *  @param	handler	Called on success. A function that takes a RequestResult<CreateResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Create(const std::map<std::string, strix::net::object::ObjectPtr> &properties, std::string playerName, core::request::
	                    RequestResultHandlerT<core::message::CreateResponse> handler, core::request::RequestFailureHandler failureHandler, core
	                    ::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request creation of a room with the given properties. The callbacks are triggered on a response from the server
	 *  @param	properties	A map of strings (property names) and objects (values) for the room properties
	 *  @param	memberProperties	A map of strings (property names) and objects (values) for the member properties (The initial room owner)
	 *  @param	handler	Called on success. A function that takes a RequestResult<CreateResponse> as input. A function that takes a RequestResult<CreateResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Create(const std::map<std::string, strix::net::object::ObjectPtr> &properties, const std::map<std::string, strix::net::object::ObjectPtr> &memberProperties, core::request::RequestResultHandlerT<core::message::CreateResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to join a room. The callbacks are triggered on a response from the server
	 *  @param	message	The join message to send
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	void Join(client::room::message::RoomJoinMessagePtr message, core::request::RequestResultHandlerT<client::room::message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr) override;

	/**
	 *  Request to join a room. The callbacks are triggered on a response from the server
	 *  @param	message	The join message to send
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Join(match::room::message::MatchRoomJoinMessagePtr message, core::request::RequestResultHandlerT<client::room::message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to join a room. The callbacks are triggered on a response from the server
	 *  @param	roomId	The id for the room to join
	 *  @param	playerName	The name of the player joining the room
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Join(long long roomId, std::string playerName, core::request::RequestResultHandlerT<client::room::message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to join a room. The callbacks are triggered on a response from the server
	 *  @param	roomId	The id for the room to join
	 *  @param	memberProperties	A map of strings (property names) and objects (values) for the joining members properties
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Join(long long roomId, const std::map<std::string, strix::net::object::ObjectPtr> &memberProperties, core::request::RequestResultHandlerT<client::room::message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to join a room. The callbacks are triggered on a response from the server
	 *  @param	roomId	The id for the room to join
	 *  @param	playerName	The name of the player joining the room
	 *  @param	password	The password for the room
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Join(long long roomId, std::string playerName, std::string password, core::request::RequestResultHandlerT<client::room::message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to join a room. The callbacks are triggered on a response from the server
	 *  @param	roomId	The id for the room to join
	 *  @param	password	The password for the room
	 *  @param	memberProperties	A map of strings (property names) and objects (values) for the joining members properties
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Join(long long roomId, std::string password, const std::map<std::string, strix::net::object::ObjectPtr> &memberProperties, core::request::RequestResultHandlerT<client::room::message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to kick a player from the room. The callbacks are triggered on a response from the server
	 *  @param	message	The message to send
	 *  @param	handler	Called on success. A function that takes a RequestResult<MatchRoomKickResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Kick(match::room::message::MatchRoomKickMessagePtr message, core::request::RequestResultHandlerT<match::room::message::MatchRoomKickResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to kick a player from the room. The callbacks are triggered on a response from the server
	 *  @param	kickedPlayerUid	The id for the player to kick
	 *  @param	handler	Called on success. A function that takes a RequestResult<MatchRoomKickResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void Kick(core::UIDPtr kickedPlayerUid, core::request::RequestResultHandlerT<match::room::message::MatchRoomKickResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request information on joinable rooms. Limit and offset parameters can be used to 
	 *  retrieve pages of rooms from the full list. The callbacks are triggered on a response from the server
	 *  @param	limit	The maximum number of results to retrieve
	 *  @param	offset	The offset into the full list to begin to retrieve from
	 *  @param	handler	Called on success. A function that takes a RequestResult<SearchResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void SearchJoinableRoom(int limit, int offset, core::request::RequestResultHandlerT<core::message::SearchResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request information on joinable rooms with some condition. Limit and offset parameters can be used to
	 *  retrieve pages of rooms from the full list. The callbacks are triggered on a response from the server
	 *  @param	condition	The condition to filter results from
	 *  @param	order	The order with which to display results
	 *  @param	limit	The maximum number of results to retrieve
	 *  @param	offset	The offset into the full list to begin to retrieve from
	 *  @param	handler	Called on success. A function that takes a RequestResult<SearchResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void SearchJoinableRoom(core::model::manager::filter::ConditionPtr condition, core::model::manager::filter::OrderPtr order, int limit, int offset, core::request::RequestResultHandlerT<core::message::SearchResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request information on joinable rooms with some condition in the message. Limit and offset parameters in the message can be used to
	 *  retrieve pages of rooms from the full list. The callbacks are triggered on a response from the server
	 *  @param	message	The message to send
	 *  @param	handler	Called on success. A function that takes a RequestResult<SearchResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void SearchJoinableRoom(core::message::SearchMessagePtr message, core::request::RequestResultHandlerT<core::message::SearchResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request the number of joinable rooms. The callbacks are triggered on a response from the server
	 *  @param	handler	Called on success. A function that takes a RequestResult<GetCountResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void GetJoinableRoomCount(core::request::RequestResultHandlerT<core::message::GetCountResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request the number of joinable rooms with some condition. The callbacks are triggered on a response from the server
	 *  @param	condition	The condition to filter results by
	 *  @param	handler	Called on success. A function that takes a RequestResult<GetCountResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void GetJoinableRoomCount(core::model::manager::filter::ConditionPtr condition, core::request::RequestResultHandlerT<core::message::GetCountResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request the number of joinable rooms with some condition in a message. The callbacks are triggered on a response from the server
	 *  @param	message	The message to send
	 *  @param	handler	Called on success. A function that takes a RequestResult<GetCountResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void GetJoinableRoomCount(core::message::GetCountMessagePtr message, core::request::RequestResultHandlerT<core::message::GetCountResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to join a random room on the room server. The callbacks are triggered on a response from the server
	 *  @param	playerName	The name of the player joining
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void JoinRandomRoom(std::string playerName, core::request::RequestResultHandlerT<client::room::message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Request to join a random room on the room server with some condition. The callbacks are triggered on a response from the server
	 *  @param	playerName	The name of the player joining
	 *  @param	condition	The condition to filter the results by
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request (timeout, etc)
	 */
	virtual void JoinRandomRoom(std::string playerName, core::model::manager::filter::ConditionPtr condition, core::request::RequestResultHandlerT<client::room::message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	using strix::client::room::RoomClient::Relay;

	/**
	 *  Relay a message. The callbacks are triggered on a response from the server
	 *  @param	object	The relay message to register a callback to
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomRelayResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Relay(net::object::ObjectPtr object, core::request::RequestResultHandlerT<client::room::message::RoomRelayResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);
	
	using strix::client::room::RoomClient::DirectRelay;

	/**
	 *  Relay a message directly to a recipient. The callbacks are triggered on a response from the server
	 *  @param	to	The UID of the recipient
	 *  @param	object	The relay message to register a callback to
	 *  @param	handler	Called on success. A function that takes a RequestResult<RoomDirectRelayResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void DirectRelay(core::UIDPtr to, net::object::ObjectPtr object, core::request::RequestResultHandlerT<client::room::message::RoomDirectRelayResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Called on a successful kick response from the server
	 *  @param	result	The information from the kick response
	 */
	virtual void OnMatchRoomKickResponse(core::request::RequestResult<match::room::message::MatchRoomKickResponsePtr> result);

	/**
	 *  Called on a failed kick response from the server
	 *  @param	result	The information from the kick response
	 */
	virtual void OnMatchRoomKickFailed(core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  Called when a player join notification is received from the server
	 *  @param	messageChannel	The channel the notification was received from
	 *  @param	message	The message containing the join information
	 */
	virtual void OnRoomJoinNotification(strix::net::message::MessageChannelPtr messageChannel, client::room::message::RoomJoinNotificationPtr message) override;

	/**
	 *  Called when a player leave notification is received from the server
	 *  @param	messageChannel	The channel the notification was received from
	 *  @param	message	The message containing the leave information
	 */
	virtual void OnRoomLeaveNotification(strix::net::message::MessageChannelPtr messageChannel, client::room::message::RoomLeaveNotificationPtr message) override;

	/**
	 *  Called when a player kick notification is received from the server
	 *  @param	messageChannel	The channel the notification was received from
	 *  @param	message	The message containing the kick information
	 */
	virtual void OnMatchRoomKickNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::MatchRoomKickNotificationPtr message);

	/**
	 *  Called when a room set notification is received from the server
	 *  @param	messageChannel	The channel the notification was received from
	 *  @param	message	The message containing the set information
	 */
	void OnRoomSetNotification(strix::net::message::MessageChannelPtr messageChannel, client::room::message::RoomSetNotificationPtr message) override;

	/**
	 *  Get the room data for this room
	 *  @returns	The room data
	 */
	client::room::RoomDataPtr GetRoomData() const override;

	/**
	 *  Set the room data for this room
	 *  @param	roomDataPtr	The room data
	 */
	void SetRoomData(client::room::RoomDataPtr roomDataPtr) override;

	/**
	 *  Get the match room data for this room
	 *  @returns	The room data
	 */
	virtual MatchRoomDataPtr GetMatchRoomData() const;

	/**
	 *  Set the match room data for this room
	 *  @param	matchRoomDataPtr	The room data
	 */
	virtual void SetMatchRoomData(MatchRoomDataPtr matchRoomDataPtr);

	/**
	 *  Return a condition that is true when the room is joinable (i.e, there is spare capacity)
	 *  @returns	The joinable condition
	 */
	virtual core::model::manager::filter::ConditionPtr MakeConditionForJoinableMatchRoom();

	/**
	 *  Add the joinable condition (i.e, there is spare capacity) to the given condition and returns
	 *  @param	oldCondition	The existing conditions
	 *  @returns	The existing conditions && the joinable condition
	 */
	virtual core::model::manager::filter::ConditionPtr MakeConditionForJoinableMatchRoom(core::model::manager::filter::ConditionPtr oldCondition);

	/**
	 *  Add a handler for when a match room kick notification is received
	 *  @param	handler	The handler
	 *  @returns	The handler
	 */
	core::util::DelegateList<>::Handle AddMatchRoomKickNotifiedHandler(MatchRoomKickNotificationEventHandler handler);

	/**
	 *  Remove the kick notified handler
	 *  @param	handle	The handle to remove
	 */
	void RemoveMatchRoomKickNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when a room set notification is received and room ownership was changed
	 *  @param	handler	The handler
	 *  @returns	The handler
	 */
	core::util::DelegateList<>::Handle AddRoomChangeOwnerNotifiedHandler(client::room::RoomSetNotificationEventHandler handler);

	/**
	 *  Remove the room owner changed notified handler
	 *  @param	handle	The handle to remove
	 */
	void RemoveRoomChangeOwnerNotifiedHandler(core::util::DelegateList<>::Handle handle);

private:
	MatchRoomDataPtr m_matchRoomData;

	MatchRoomNotificationListenerPtr m_notificationListener;

	core::util::DelegateList<core::NotificationEventArgs<room::message::MatchRoomKickNotificationPtr>> m_matchRoomKickNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<client::room::message::RoomSetNotificationPtr>> m_roomChangeOwnerDelegate;
};

} } }