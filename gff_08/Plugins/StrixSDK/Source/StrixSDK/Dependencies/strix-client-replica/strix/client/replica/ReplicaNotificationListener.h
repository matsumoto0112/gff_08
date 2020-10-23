#pragma once

#include <strix/net/object/MetaClass.h>

#include <memory>

namespace strix { namespace net { namespace message {
class MessageChannel;
typedef std::shared_ptr<MessageChannel> MessageChannelPtr;
} } }

namespace strix { namespace client { namespace core { namespace message {
class DefaultParameterMessageDispatcher;
typedef std::shared_ptr<DefaultParameterMessageDispatcher> DefaultParameterMessageDispatcherPtr;
} } } }

namespace strix { namespace client { namespace replica { namespace message {
class ReplicaCreateNotification;
class ReplicaSetNotification;
class ReplicaDeleteNotification;
class ReplicaChangeOwnerNotification;
typedef std::shared_ptr<ReplicaCreateNotification> ReplicaCreateNotificationPtr;
typedef std::shared_ptr<ReplicaSetNotification> ReplicaSetNotificationPtr;
typedef std::shared_ptr<ReplicaDeleteNotification> ReplicaDeleteNotificationPtr;
typedef std::shared_ptr<ReplicaChangeOwnerNotification> ReplicaChangeOwnerNotificationPtr;
} } } }

namespace strix { namespace client { namespace replica {

class ReplicaClient;

/**
 *  A listener for replica specific notifications such as creation and deletion
 */
class ReplicaNotificationListener
{
public:
	ReplicaNotificationListener(const net::object::MetaClass &replicaClass);
	virtual ~ReplicaNotificationListener();

	/**
	 *  Add the dispatcher and attach this listeners notification handlers to it
	 *  @param	dispatcher	The dispatcher containing the message handlers
	 */
	virtual void AddMessageHandlers(core::message::DefaultParameterMessageDispatcherPtr dispatcher);

	/**
	 *  Remove message handlers
	 */
	virtual void RemoveMessageHandlers();

	/**
	 *  Called when a replica create notification is received from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	msg	The message containing info about the notification
	 */
	virtual void OnReplicaCreateNotification(strix::net::message::MessageChannelPtr messageChannel, replica::message::ReplicaCreateNotificationPtr msg) = 0;

	/**
	 *  Called when a replica set notification is received from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	msg	The message containing info about the notification
	 */
	virtual void OnReplicaSetNotification(strix::net::message::MessageChannelPtr messageChannel, replica::message::ReplicaSetNotificationPtr msg) = 0;

	/**
	 *  Called when a replica delete notification is received from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	msg	The message containing info about the notification
	 */
	virtual void OnReplicaDeleteNotification(strix::net::message::MessageChannelPtr messageChannel, replica::message::ReplicaDeleteNotificationPtr msg) = 0;

	/**
	 *  Called when a replica change owner notification is received from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	msg	The message containing info about the notification
	 */
	virtual void OnReplicaChangeOwnerNotification(strix::net::message::MessageChannelPtr messageChannel, replica::message::ReplicaChangeOwnerNotificationPtr msg) = 0;

protected:
	/**
	 *  Add default message handlers
	 */
	void AddDefaultMessageHandlers();

	/**
	 *  Remove default message handlers
	 */
	void RemoveDefaultMessageHandlers();

	core::message::DefaultParameterMessageDispatcherPtr m_messageDispatcher;
	const net::object::MetaClass &m_replicaClass;
};

class DefaultReplicaNotificationListener : public ReplicaNotificationListener
{
public:
	DefaultReplicaNotificationListener(ReplicaClient *replicaClient);

	/**
	 *  Called when a replica create notification is received from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	msg	The message containing info about the notification
	 */
	virtual void OnReplicaCreateNotification(strix::net::message::MessageChannelPtr messageChannel, replica::message::ReplicaCreateNotificationPtr msg) override;

	/**
	 *  Called when a replica set notification is received from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	msg	The message containing info about the notification
	 */
	virtual void OnReplicaSetNotification(strix::net::message::MessageChannelPtr messageChannel, replica::message::ReplicaSetNotificationPtr msg) override;

	/**
	 *  Called when a replica delete notification is received from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	msg	The message containing info about the notification
	 */
	virtual void OnReplicaDeleteNotification(strix::net::message::MessageChannelPtr messageChannel, replica::message::ReplicaDeleteNotificationPtr msg) override;

	/**
	 *  Called when a replica change owner notification is received from the server
	 *  @param	messageChannel	The channel the notification was received on
	 *  @param	msg	The message containing info about the notification
	 */
	virtual void OnReplicaChangeOwnerNotification(strix::net::message::MessageChannelPtr messageChannel, replica::message::ReplicaChangeOwnerNotificationPtr msg) override;

protected:
	ReplicaClient *m_replicaClient;
};

typedef std::shared_ptr<ReplicaNotificationListener> ReplicaNotificationListenerPtr;

} } }
