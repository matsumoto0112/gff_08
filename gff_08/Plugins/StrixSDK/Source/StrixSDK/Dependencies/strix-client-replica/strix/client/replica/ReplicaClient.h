#pragma once

#include <strix/client/core/CRUDClient.h>
#include <strix/client/core/NotificationEventArgs.h>
#include <strix/client/core/util/Delegates.h>
#include <strix/net/message/MessageChannelListener.h>
#include <strix/client/replica/message/ReplicaCreateResponse.h>

#include <memory>

namespace strix { namespace client { namespace room {

class RoomClient;
class RoomLeftEventArgs;
class RoomDeletedEventArgs;

} } }

namespace strix { namespace client { namespace replica { namespace message {
	
class ReplicaCreateMessage;
class ReplicaCreateResponse;
class ReplicaCreateNotification;
class ReplicaSetMessage;
class ReplicaSetNotification;
class ReplicaDeleteNotification;
class ReplicaChangeOwnerNotification;

typedef std::shared_ptr<ReplicaCreateMessage> ReplicaCreateMessagePtr;
typedef std::shared_ptr<ReplicaCreateResponse> ReplicaCreateResponsePtr;
typedef std::shared_ptr<ReplicaCreateNotification> ReplicaCreateNotificationPtr;
typedef std::shared_ptr<ReplicaSetNotification> ReplicaSetNotificationPtr;
typedef std::shared_ptr<ReplicaSetMessage> ReplicaSetMessagePtr;
typedef std::shared_ptr<ReplicaDeleteNotification> ReplicaDeleteNotificationPtr;
typedef std::shared_ptr<ReplicaChangeOwnerNotification> ReplicaChangeOwnerNotificationPtr;

} } } }

namespace strix { namespace client { namespace replica {

class ReplicaData;
typedef std::shared_ptr<ReplicaData> ReplicaDataPtr;

class ReplicaNotificationListener;
typedef std::shared_ptr<ReplicaNotificationListener> ReplicaNotificationListenerPtr;

typedef std::function<void(core::NotificationEventArgs<message::ReplicaCreateNotificationPtr>)> ReplicaCreateNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::ReplicaSetNotificationPtr>)> ReplicaSetNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::ReplicaDeleteNotificationPtr>)> ReplicaDeleteNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::ReplicaChangeOwnerNotificationPtr>)> ReplicaChangeOwnerNotificationEventHandler;

class ReplicaClient : public core::CRUDClient
{
public:
	ReplicaClient(const strix::net::object::MetaClass &replicaClass);

	ReplicaClient(const strix::net::object::MetaClass &replicaClass, ReplicaDataPtr replicaData);

	virtual ~ReplicaClient();

	/**
	 *  Get the replica data
	 *  @returns	The stored replica data
	 */
	virtual ReplicaDataPtr GetReplicaData();

	/**
	 *  Set the replica data
	 *  @param	replicaData	The replica data to set
	 */
	virtual void SetReplicaData(ReplicaDataPtr replicaData);

	/**
	 *  Initialize the replica client
	 *  @param	messageChannel	The message channel to use for sending/receiving messages
	 *  @param	requestDispatcher	The request dispatcher to use for sending/receiving requests
	 */
	void Init(strix::net::message::MessageChannelPtr messageChannel, core::request::RequestDispatcherPtr requestDispatcher) override;

	/**
	 *  Add the room client event handlers
	 *  @param	roomClient	The room client to add the events on
	 */
	void AddRoomEventHandlers(std::shared_ptr<room::RoomClient> roomClient);

	/**
	 *  Remove the room client event handlers
	 */
	void RemoveRoomEventHandlers();

	/**
	 *  Add the message handlers to the provided message dispatcher
	 */
	void AddMessageHandlers(const strix::client::core::message::DefaultParameterMessageDispatcherPtr &messageDispatcher) override;

	/**
	 *  Remove the message handlers from the message dispatcher
	 */
	void RemoveMessageHandlers() override;

	/**
	 *  Get the replica notification listener used by this client
	 *  @returns	The replica notification listener used by this client
	 */
	ReplicaNotificationListenerPtr GetReplicaNotificationListener();

	/**
	 *  Send a create message. The callbacks are triggered on a response from the server
	 *  @param	message	The replica create message that will be sent
	 *  @param	handler	Called on success. A function that takes a RequestResult<CreateRespone> as input
	 *  @param	failureHandler	Called on failure. A function that takes a RequestResult<FailureMessage> as input
	 *  @param	config	The configuration structure of this request
	 *  @remark	In general the override taking ReplicaCreateMessagePtr should be used
	 */
	void Create(core::message::CreateMessagePtr message, core::request::RequestResultHandlerT<core::message::CreateResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr) override;

	/**
	 *  Send a replica create message. The callbacks are triggered on a response from the server
	 *  @param	message	The replica create message that will be sent
	 *  @param	handler	Called on success. A function that takes a RequestResult<ReplicaCreateResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a RequestResult<FailureMessage> as input
	 *  @param	config	The configuration structure of this request
	 */
	virtual void Create(message::ReplicaCreateMessagePtr message, core::request::RequestResultHandlerT<message::ReplicaCreateResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Send a set message. The callbacks are triggered on a response from the server
	 *  @param	message	The replica set message that will be sent
	 *  @param	handler	Called on success. A function that takes a RequestResult<SetResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a RequestResult<FailureMessage> as input
	 *  @param	config	The configuration structure of this request
	 *  @remark	In general the override taking ReplicaSetMessagePtr should be used
	 */
	void Set(core::message::SetMessagePtr message, core::request::RequestResultHandlerT<core::message::SetResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr) override;

	/**
	 *  Send a replica set message. The callbacks are triggered on a response from the server
	 *  @param	message	The replica set message that will be sent
	 *  @param	handler	Called on success. A function that takes a RequestResult<SetResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a RequestResult<FailureMessage> as input
	 *  @param	config	The configuration structure of this request
	 */
	virtual void Set(message::ReplicaSetMessagePtr message, core::request::RequestResultHandlerT<core::message::SetResponse> handler, core::request::RequestFailureHandler failureHandler, core::request::RequestConfigPtr config = nullptr);

	/**
	 *  Send a replica delete message. The callbacks are triggered on a response from the server
	 *  @param	message	The replica delete message that will be sent
	 *  @param	handler	Called on success. A function that takes a RequestResult<DeleteResponse> as input
	 *  @param	failureHandler	Called on failure. A function that takes a RequestResult<FailureMessage> as input
	 *  @param	config	The configuration structure of this request
	 */
	void Delete(core::message::DeleteMessagePtr message, 
		core::request::RequestResultHandlerT<core::message::DeleteResponse> handler, 
		core::request::RequestFailureHandler failureHandler,
		core::request::RequestConfigPtr config = nullptr) override;

	/**
	 *  Event called when a create response has been received
	 *  @param	result	The response message packed in the RequestResult structure
	 */
	void OnCreateResponse(core::request::RequestResult<std::shared_ptr<core::message::CreateResponse>> result) override;

	/**
	 *  Event called when a delete by response has been received
	 *  @param	result	The response message packed in the RequestResult structure
	 */
	void OnDeleteByResponse(core::request::RequestResult<std::shared_ptr<core::message::DeleteByResponse>> result) override;

	/**
	 *  Event called when a delete response has been received
	 *  @param	result	The response message packed in the RequestResult structure
	 */
	void OnDeleteResponse(core::request::RequestResult<std::shared_ptr<core::message::DeleteResponse>> result) override;

	/**
	 *  Event called when a delete failed message has been received
	 *  @param	result	The failure message packed in the RequestResult structure
	 */
	void OnDeleteFailed(core::request::RequestResult<std::shared_ptr<core::message::FailureMessage>> result) override;

	/**
	 *  Event called when a set by response has been received
	 *  @param	result	The response message packed in the RequestResult structure
	 */
	void OnSetByResponse(core::request::RequestResult<std::shared_ptr<core::message::SetByResponse>> result) override;

	/**
	 *  Event called when a set response has been received
	 *  @param	result	The response message packed in the RequestResult structure
	 */
	void OnSetResponse(core::request::RequestResult<std::shared_ptr<core::message::SetResponse>> result) override;

	/**
	 *  Event called when a replica create response has been received
	 *  @param	result	The response message packed in the RequestResult structure
	 */
	virtual void OnReplicaCreateResponse(core::request::RequestResult<std::shared_ptr<message::ReplicaCreateResponse>> result);

	/**
	 *  Event called when a replica create notification has been received
	 *  @param	messageChannel	The message channel this notification arrived on
	 *  @param	message	Received notification
	 */
	virtual void OnReplicaCreateNotification(strix::net::message::MessageChannelPtr messageChannel, message::ReplicaCreateNotificationPtr message);

	/**
	 *  Event called when a replica set notification has been received
	 *  @param	messageChannel	The message channel this notification arrived on
	 *  @param	message	Received notification
	 */
	virtual void OnReplicaSetNotification(strix::net::message::MessageChannelPtr messageChannel, message::ReplicaSetNotificationPtr message);

	/**
	 *  Event called when a replica change owner notification has been received
	 *  @param	messageChannel	The message channel this notification arrived on
	 *  @param	message	Received notification
	 */
	virtual void OnReplicaChangeOwnerNotification(strix::net::message::MessageChannelPtr messageChannel, message::ReplicaChangeOwnerNotificationPtr message);

	/**
	 *  Event called when a replica delete notification has been received
	 *  @param	messageChannel	The message channel this notification arrived on
	 *  @param	message	Received notification
	 */
	virtual void OnReplicaDeleteNotification(strix::net::message::MessageChannelPtr messageChannel, message::ReplicaDeleteNotificationPtr message);

	/**
	 *  Add a new handler to the replica create notification received delegate
	 *  @param	handler	The handler to add
	 *  @returns	The key of the added handle
	 */
	core::util::DelegateList<>::Handle AddReplicaCreateNotifiedHandler(ReplicaCreateNotificationEventHandler handler);

	/**
	 *  Remove a handler from the replica create notification received delegate
	 *  @param	handle	The key of the handle to remove
	 */
	void RemoveReplicaCreateNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a new handler to the replica set notification received delegate
	 *  @param	handler	The handler to add
	 *  @returns	The key of the added handle
	 */
	core::util::DelegateList<>::Handle AddReplicaSetNotifiedHandler(ReplicaSetNotificationEventHandler handler);

	/**
	 *  Remove a handler from the replica set notification received delegate
	 *  @param	handle	The key of the handle to remove
	 */
	void RemoveReplicaSetNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a new handler to the replica delete notification received delegate
	 *  @param	handler	The handler to add
	 *  @returns	The key of the added handle
	 */
	core::util::DelegateList<>::Handle AddReplicaDeleteNotifiedHandler(ReplicaDeleteNotificationEventHandler handler);

	/**
	 *  Remove a handler from the replica delete notification received delegate
	 *  @param	handle	The key of the handle to remove
	 */
	void RemoveReplicaDeleteNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a new handler to the replica change owner notification received delegate
	 *  @param	handler	The handler to add
	 *  @returns	The key of the added handle
	 */
	core::util::DelegateList<>::Handle AddReplicaChangeOwnerNotifiedHandler(ReplicaChangeOwnerNotificationEventHandler handler);

	/**
	 *  Remove a handler from the replica change owner notification received delegate
	 *  @param	handle	The key of the handle to remove
	 */
	void RemoveReplicaChangeOwnerNotifiedHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler to be called on a create response to update routing listener
	 *  @param	handler	The function to be called. Function must take a replica ID and a room ID
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddReplicaCreateResponseHandler(std::function<void(long long, long long)> handler);

	/**
	 *  Remove the given handler from the on create response delegate list
	 *  @param	handle	The key to the handler to remove
	 */
	void RemoveReplicaCreateResponseHandler(core::util::DelegateList<>::Handle handle);

	/**
	 *  Add a handler to be called on a delete response to update routing listener
	 *  @param	handler	The function to be called. Function must take a replica ID and a room ID
	 *  @returns	The key to the added handler
	 */
	core::util::DelegateList<>::Handle AddReplicaDeleteResponseHandler(std::function<void(long long)> handler);

	 /**
	  *  Remove the given handler from the on delete response delegate list
	  *  @param	handle	The key to the handler to remove
	  */
	void RemoveReplicaDeleteResponseHander(core::util::DelegateList<>::Handle handle);

protected:

	/**
	 *  Add a listener for the given message channel. Can only have one listener at a time
	 *  @param	messageChannel	The message channel to listen on
	 */
	void AddMessageChannelListener(const strix::net::message::MessageChannelPtr &messageChannel);

	/**
	 *  Remove the message channel listener
	 */
	void RemoveMessageChannelListener();

	/**
	 *  Reset the replica data
	 */
	virtual void ResetData();

	/**
	 *  Remove all replicas with the given room id from the internal replica data
	 *  @param	roomId	The room id
	 */
	void RemoveReplicasByRoomId(long long roomId);

	/**
	 *  A message channel listener for replica client
	 */
	class ReplicaClientMessageChannelListener : public strix::net::message::MessageChannelListener
	{
	public:
		ReplicaClientMessageChannelListener(ReplicaClient *replicaClient);

		/**
		 *  Called when message channel connects
		 *  @param	ev	The event object containing information about the connection
		 */
		void OnConnect(const MessageChannelConnectEvent &ev) override;

		/**
		 *  Called on message received from the message channel
		 *  @param	ev	The event object containing information about the message
		 */
		void OnMessage(const MessageChannelMessageEvent &ev) override;

		/**
		 *  Called on close of connection to the message channel. Resets replica data
		 *  @param	ev	The event object containing information about the close
		 */
		void OnClose(const MessageChannelCloseEvent &ev) override;

		/**
		 *  Called when message channel encounters an error
		 *  @param	ev	The event object containing information about the connection
		 */
		void OnError(const MessageChannelErrorEvent &ev) override;

		/**
		 *  Called on detach from the message channel
		 */
		void OnDetach() override;

		/**
		 *  Invalidate replica data (sets to null)
		 */
		void Invalidate();
	private:
		ReplicaClient *m_replicaClient;
	};

private:
	void HandleRoomLeftEvent(room::RoomLeftEventArgs eventArgs);
	void HandleRoomDeletedEvent(room::RoomDeletedEventArgs eventArgs);

	ReplicaDataPtr m_replicaData;
	ReplicaNotificationListenerPtr m_notificationListener;
	std::shared_ptr<ReplicaClientMessageChannelListener> m_messageChannelListener;
	std::weak_ptr<core::message::DefaultParameterMessageDispatcher> m_messageDispatcher;

	
	std::weak_ptr<room::RoomClient> m_roomClient;
	core::util::DelegateList<>::Handle m_roomLeftDelegateHandle;
	core::util::DelegateList<>::Handle m_roomDeletedDelegateHandle;

	core::util::DelegateList<core::NotificationEventArgs<message::ReplicaCreateNotificationPtr> > m_replicaCreateNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::ReplicaSetNotificationPtr> > m_replicaSetNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::ReplicaDeleteNotificationPtr> > m_replicaDeleteNotifiedDelegate;
	core::util::DelegateList<core::NotificationEventArgs<message::ReplicaChangeOwnerNotificationPtr> > m_replicaChangeOwnerNotifiedDelegate;

	core::util::DelegateList<long long, long long> m_replicaCreateResponseDelegate;
	core::util::DelegateList<long long> m_replicaDeleteResponseDelegate;
};

class ReplicaClient;
typedef std::shared_ptr<ReplicaClient> ReplicaClientPtr;

} } }
