#pragma once

#include <strix/net/object/MetaClass.h>
#include <strix/net/message/MessageChannelListener.h>
#include <strix/client/core/CRUDClient.h>
#include <strix/client/core/NotificationEventArgs.h>
#include <strix/client/core/util/Delegates.h>
#include <strix/client/room/model/Room.h>
#include <strix/client/room/model/RoomMember.h>
#include <strix/client/room/RoomData.h>
#include <strix/client/room/RoomEvents.h>
#include <strix/client/room/RoomMessages.h>

namespace strix { namespace client { namespace room {
	
class RoomNotificationListener;
typedef std::shared_ptr<RoomNotificationListener> RoomNotificationListenerPtr;

/**
 *  Controller class for a room.
 *  Provides methods creating and leaving rooms, sending relay messages, and other functions
 */
class RoomClient : public core::CRUDClient, public std::enable_shared_from_this<RoomClient>
{
public:
	RoomClient(const strix::net::object::MetaClass &roomClass, const strix::net::object::MetaClass &roomMemberClass);
	RoomClient(RoomDataPtr roomData, const strix::net::object::MetaClass &roomClass, const strix::net::object::MetaClass &roomMemberClass);

	virtual ~RoomClient();

	/**
	 *  Return the class of the room member for this client
	 *  @returns	The room member's MetaClass
	 */
	const strix::net::object::MetaClass &GetRoomMemberClass() const {
		return *m_roomMemberClass;
	}

	/**
	 *  Initialize this room client
	 *  @param	messageChannel	The message channel to connect on
	 *  @param	requestDispatcher	The dispatcher to use for requests
	 */
	void Init(strix::net::message::MessageChannelPtr messageChannel, core::request::RequestDispatcherPtr requestDispatcher) override;

	/**
	 *  Add the dispatcher to this client. Attaches this client's listener's handlers to the dispatcher
	 *  @param	dispatcher	The message dispatcher containing the handlers
	 */
	void AddMessageHandlers(const core::message::DefaultParameterMessageDispatcherPtr &messageDispatcher) override;

	/**
	 *  Remove message handlers
	 */
	void RemoveMessageHandlers() override;

	/**
	 *  Get the room notification listener for this client
	 *  @returns	The listener
	 */
	RoomNotificationListenerPtr GetRoomNotificationListener() const;

	/**
	 *  Called when a create room response is received from the server
	 *  @param	requestResult	The result contained in the response
	 */
	void OnCreateResponse(core::request::RequestResult<core::message::CreateResponsePtr> requestResult) override;

	/**
	 *  Called when a delete room response is received from the server
	 *  @param	result	The result contained in the response
	 */
	void OnDeleteResponse(core::request::RequestResult<core::message::DeleteResponsePtr> result) override;

	/**
	 *  Called when a set room properties response is received from the server
	 *  @param	result	The result contained in the response
	 */
	void OnSetResponse(core::request::RequestResult<core::message::SetResponsePtr> result) override;

	/**
	 *  Called when a conditional set room properties response is received from the server
	 *  @param	result	The result contained in the response
	 */
	void OnSetByResponse(core::request::RequestResult<core::message::SetByResponsePtr> result) override;

	/**
	 *  Create a room. The callbacks are triggered on a create response from the server
	 *  @param	message	The create message to register a callback to
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<CreateResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	void Create(core::message::CreateMessagePtr message, core::request::RequestResultHandlerT<core::message::CreateResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr) override;

	/**
	 *  Create a room. The callbacks are triggered on a create response from the server
	 *  @param	message	The create message to register a callback to
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<CreateResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Create(message::RoomCreateMessagePtr message, core::request::RequestResultHandlerT<message::RoomCreateResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	using CRUDClient::Delete;

	/**
	 *  Delete a room. The callbacks are triggered on a delete response from the server
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<DeleteResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Delete(core::request::RequestResultHandlerT<core::message::DeleteResponse> handler, core::request::RequestFailureHandler failureHandler, std::shared_ptr<core::request::RequestConfig> config = nullptr);

	using CRUDClient::Set;

	/**
	 *  Set the properties on a room. The callbacks are triggered on a properties set response from the server
	 *  @param	roomId	The room to modify
	 *  @param	roomProperties	A map of property names to values
	 *  @param	handler	The callback to call on success. A function that takes a RequestResult<SetResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Set(long long roomId, std::map<std::string, strix::net::object::ObjectPtr> roomProperties, core::request::RequestResultHandlerT<core::message::SetResponse> handler, core::request::RequestFailureHandler failureHandler, std::shared_ptr<core::request::RequestConfig> config = nullptr);

	/**
	 *  Set the properties on a room. The callbacks are triggered on a properties set response from the server
	 *  @param	roomProperties	A map of property names to values
	 *  @param	handler	The callback to call on success. A function that takes a RequestResult<SetResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Set(std::map<std::string, strix::net::object::ObjectPtr> roomProperties, core::request::RequestResultHandlerT<core::message::SetResponse> handler, core::request::RequestFailureHandler failureHandler, std::shared_ptr<core::request::RequestConfig> config = nullptr);

	/**
	 *  Join a room. The callbacks are triggered on a join response from the server
	 *  @param	message	The join message to register a callback to
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomJoinResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Join(message::RoomJoinMessagePtr message, core::request::RequestResultHandlerT<message::RoomJoinResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Leave a room. The callbacks are triggered on a leave response from the server
	 *  @param	message	The leave message to register a callback to
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomLeaveResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Leave(message::RoomLeaveMessagePtr message, core::request::RequestResultHandlerT<message::RoomLeaveResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Leave a room. The callbacks are triggered on a leave response from the server
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomLeaveResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Leave(core::request::RequestResultHandlerT<message::RoomLeaveResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Get the members of this room. The callbacks are triggered on a get members response from the server
	 *  @param	message	The get members message to register a callback to
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomGetMembersResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void GetMembers(message::RoomGetMembersMessagePtr message, core::request::RequestResultHandlerT<message::RoomGetMembersResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the properties of a member of this room. The callbacks are triggered on a set member response from the server
	 *  @param	message	The set member message to register a callback to
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomSetMemberResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void SetMember(message::RoomSetMemberMessagePtr message, core::request::RequestResultHandlerT<message::RoomSetMemberResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the properties of a member of this room. The callbacks are triggered on a set member response from the server
	 *  @param	memberId	The member to set properties on
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomSetMemberResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void SetMember(long long memberId, std::map<std::string, strix::net::object::ObjectPtr> memberProperties, core::request::RequestResultHandlerT<message::RoomSetMemberResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Set the properties of a member in this room. The member is the player this client represents. The callbacks are triggered on a set member response from the server
	 *  @param	memberProperties	The member properties to set on this member
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomSetMemberResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void SetMember(std::map<std::string, strix::net::object::ObjectPtr> memberProperties, core::request::RequestResultHandlerT<message::RoomSetMemberResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Relay a message. The callbacks are triggered on a relay response from the server
	 *  @param	message	The relay message to register a callback to
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomRelayResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void Relay(message::RoomRelayMessagePtr message, core::request::RequestResultHandlerT<message::RoomRelayResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Direct relay a message. The callbacks are triggered on a relay response from the server
	 *  @param	message	The direct relay message to register a callback to
	 *  @param	handler	The callback to call on successful response. A function that takes a RequestResult<RoomDirectRelayResponse> as input
	 *  @param	failureHandler	The callback to call on failure. A function that takes a FailureMessage as input
	 *  @param	config	Additional parameters for the request
	 */
	virtual void DirectRelay(message::RoomDirectRelayMessagePtr message, core::request::RequestResultHandlerT<message::RoomDirectRelayResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Called when a room create response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomCreateResponse(core::request::RequestResult<message::RoomCreateResponsePtr> result);

	/**
	 *  Called when a successful room join response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomJoinResponse(core::request::RequestResult<message::RoomJoinResponsePtr> result);

	/**
	 *  Called when a failed room join response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomJoinFailed(core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  Called when a successful room leave response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomLeaveResponse(core::request::RequestResult<message::RoomLeaveResponsePtr> result);

	/**
	 *  Called when a failed room leave response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomLeaveFailed(core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  Called when a successful room get members response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomGetMembersResponse(core::request::RequestResult<message::RoomGetMembersResponsePtr> result);

	/**
	 *  Called when a failed room get members response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomGetMembersFailed(core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  Called when a successful room set member response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomSetMemberResponse(core::request::RequestResult<message::RoomSetMemberResponsePtr> result);

	/**
	 *  Called when a failed room set member response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomSetMemberFailed(core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  Called when a successful room relay response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomRelayResponse(core::request::RequestResult<message::RoomRelayResponsePtr> result);

	/**
	 *  Called when a failed room relay response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomRelayFailed(core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  Called when a successful room direct relay response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomDirectRelayResponse(core::request::RequestResult<message::RoomDirectRelayResponsePtr> result);

	/**
	 *  Called when a failed room direct relay response is received from the server
	 *  @param	result	The result from the response
	 */
	virtual void OnRoomDirectRelayFailed(core::request::RequestResult<core::message::FailureMessagePtr> result);

	/**
	 *  Called on a room join notification from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	message	The message
	 */
	virtual void OnRoomJoinNotification(strix::net::message::MessageChannelPtr messageChannel, message::RoomJoinNotificationPtr message);

	/**
	 *  Called on a room leave notification from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	message	The message
	 */
	virtual void OnRoomLeaveNotification(strix::net::message::MessageChannelPtr messageChannel, message::RoomLeaveNotificationPtr message);

	/**
	 *  Called on a room delete notification from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	message	The message
	 */
	virtual void OnRoomDeleteNotification(strix::net::message::MessageChannelPtr messageChannel, message::RoomDeleteNotificationPtr message);

	/**
	 *  Called on a room set notification from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	message	The message
	 */
	virtual void OnRoomSetNotification(strix::net::message::MessageChannelPtr messageChannel, message::RoomSetNotificationPtr message);

	/**
	 *  Called on a room set member notification from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	message	The message
	 */
	virtual void OnRoomSetMemberNotification(strix::net::message::MessageChannelPtr messageChannel, message::RoomSetMemberNotificationPtr message);

	/**
	 *  Called on a room relay notification from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	message	The message
	 */
	virtual void OnRoomRelayNotification(strix::net::message::MessageChannelPtr messageChannel, message::RoomRelayNotificationPtr message);

	/**
	 *  Called on a room direct relay notification from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	message	The message
	 */
	virtual void OnRoomDirectRelayNotification(strix::net::message::MessageChannelPtr messageChannel, message::RoomDirectRelayNotificationPtr message);

	/**
	 *  Return the room data for the room stored on this client
	 *  @returns	The room data
	 */
	virtual RoomDataPtr GetRoomData() const;

	/**
	 *  Set the room data for the room stored on this client
	 *  @param	roomDataPtr	The room data to set
	 */
	virtual void SetRoomData(RoomDataPtr roomDataPtr);

	/**
	 *  Add a handler for when the room is created
	 *  @param	handler	The handler to add. A function that takes RoomCreatedEventArgs as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomCreatedHandler(RoomCreatedEventHandler handler);

	/**
	 *  Remove room created handler 
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomCreatedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when the room is set
	 *  @param	handler	The handler to add. A function that takes RoomSetEventArgs as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomSetHandler(RoomSetEventHandler handler);

	/**
	 *  Remove room set handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomSetHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when the room is deleted
	 *  @param	handler	The handler to add. A function that takes RoomDeletedEventArgs as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomDeletedHandler(RoomDeletedEventHandler handler);

	/**
	 *  Remove room deleted handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomDeletedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when the room is joined
	 *  @param	handler	The handler to add. A function that takes RoomJoinedEventArgs as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomJoinedHandler(RoomJoinedEventHandler handler);

	/**
	 *  Remove room joined handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomJoinedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when the room is left
	 *  @param	handler	The handler to add. A function that takes RoomLeftEventArgs as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomLeftHandler(RoomLeftEventHandler handler);

	/**
	 *  Remove room left handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomLeftHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when notified of room join
	 *  @param	handler	The handler to add. A function that takes NotificationEventArgs<RoomJoinNotificationPtr> as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomJoinNotifiedHandler(RoomJoinNotificationEventHandler handler);

	/**
	 *  Remove room join notification handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomJoinNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when notified of room leave
	 *  @param	handler	The handler to add. A function that takes NotificationEventArgs<RoomLeaveNotificationPtr> as input
	 *  @returns	The key of the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomLeaveNotifiedHandler(RoomLeaveNotificationEventHandler handler);

	/**
	 *  Remove room leave notification handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomLeaveNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when notified of room delete
	 *  @param	handler	The handler to add. A function that takes NotificationEventArgs<RoomDeleteNotificationPtr> as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomDeleteNotifiedHandler(RoomDeleteNotificationEventHandler handler);

	/**
	 *  Remove room delete notification handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomDeleteNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when notified of room set
	 *  @param	handler	The handler to add. A function that takes NotificationEventArgs<RoomSetNotificationPtr> as input
	 *  @returns	The key of the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomSetNotifiedHandler(RoomSetNotificationEventHandler handler);

	/**
	 *  Remove room set notification handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomSetNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when notified of room set member
	 *  @param	handler	The handler to add. A function that takes NotificationEventArgs<RoomSetMemberNotificationPtr> as input
	 *  @returns	The key of the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomSetMemberNotifiedHandler(RoomSetMemberNotificationEventHandler handler);

	/**
	 *  Remove room set member notification handler
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveRoomSetMemberNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when notified of room relay
	 *  @param	handler	The handler to add. A function that takes NotificationEventArgs<RoomRelayNotificationPtr> as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomRelayNotifiedHandler(RoomRelayNotificationEventHandler handler);

	/**
	 *  Remove room relay notification handler
	 *  @param	handle	The key of the handler to remove
	 */
	void RemoveRoomRelayNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler for when notified of room direct relay
	 *  @param	handler	The handler to add. A function that takes NotificationEventArgs<RoomDirectRelayNotificationPtr> as input
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddRoomDirectRelayNotifiedHandler(RoomDirectRelayNotificationEventHandler handler);

	/**
	 *  Remove room direct relay notification handler
	 *  @param	handle	The key of the handler to remove
	 */
	void RemoveRoomDirectRelayNotifiedHandler(core::util::DelegateList<>::Handle handle);

protected:

	/**
	 *  Add a message channel listener
	 *  @param	messageChannel	The message channel to add
	 */
	void AddMessageChannelListener(const strix::net::message::MessageChannelPtr &messageChannel);

	/**
	 *  Remove the message channel listener
	 */
	void RemoveMessageChannelListener();

	/**
	 *  Set this client's room data values to null
	 */
	virtual void ResetData();

	const strix::net::object::MetaClass * m_roomMemberClass;

	core::util::DelegateList<RoomCreatedEventArgs> m_roomCreatedDelegate;
	core::util::DelegateList<RoomSetEventArgs> m_roomSetDelegate;
	core::util::DelegateList<RoomDeletedEventArgs> m_roomDeletedDelegate;
	core::util::DelegateList<RoomJoinedEventArgs> m_roomJoinedDelegate;
	core::util::DelegateList<RoomLeftEventArgs> m_roomLeftDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::RoomJoinNotificationPtr>> m_roomJoinNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::RoomLeaveNotificationPtr>> m_roomLeaveNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::RoomDeleteNotificationPtr>> m_roomDeleteNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::RoomSetNotificationPtr>> m_roomSetNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::RoomSetMemberNotificationPtr>> m_roomSetMemberNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::RoomRelayNotificationPtr>> m_roomRelayNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::RoomDirectRelayNotificationPtr>> m_roomDirectRelayNotifiedDelegate;

	/**
	 *  A message channel listener for room clients
	 */
	class RoomClientMessageChannelListener : public strix::net::message::MessageChannelListener
	{
	public:

		RoomClientMessageChannelListener(RoomClient *roomClient) : m_roomClient(roomClient) {}

		/**
		 *  Called when connection is made
		 *  @param	ev	The event object containing information about the connection event
		 */
		void OnConnect(const MessageChannelConnectEvent &ev) override {}

		/**
		 *  Called when message is received from the server
		 *  @param	ev	The event object containing information about the message event
		 */
		void OnMessage(const MessageChannelMessageEvent &ev) override {}

		/**
		 *  Called when connection is closed. Resets the room client's data
		 *  @param	ev	The event object containing information about the close event
		 */
		void OnClose(const MessageChannelCloseEvent &ev) override
		{
			if (m_roomClient)
			{
				m_roomClient->ResetData();
			}
		}

		/**
		 *  Called when message channel encounters an error
		 *  @param	ev	The event object containing information about the error event
		 */
		void OnError(const MessageChannelErrorEvent &ev) override {}

		/**
		 *  Called on detach
		 */
		void OnDetach() override {}

		/**
		 *  Null room client
		 */
		void Invalidate()
		{
			m_roomClient = nullptr;
		}
	private:
		RoomClient *m_roomClient;
	};

private:
	RoomDataPtr m_roomData;
	RoomNotificationListenerPtr m_notificationListener;
	std::shared_ptr<RoomClientMessageChannelListener> m_messageChannelListener;
};

} } }
