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

namespace strix { namespace client { namespace room { namespace message {
class RoomJoinNotification;
class RoomLeaveNotification;
class RoomDeleteNotification;
class RoomSetNotification;
class RoomSetMemberNotification;
class RoomRelayNotification;
class RoomDirectRelayNotification;
typedef std::shared_ptr<RoomJoinNotification> RoomJoinNotificationPtr;
typedef std::shared_ptr<RoomLeaveNotification> RoomLeaveNotificationPtr;
typedef std::shared_ptr<RoomDeleteNotification> RoomDeleteNotificationPtr;
typedef std::shared_ptr<RoomSetNotification> RoomSetNotificationPtr;
typedef std::shared_ptr<RoomSetMemberNotification> RoomSetMemberNotificationPtr;
typedef std::shared_ptr<RoomRelayNotification> RoomRelayNotificationPtr;
typedef std::shared_ptr<RoomDirectRelayNotification> RoomDirectRelayNotificationPtr;
} } } }

namespace strix { namespace client { namespace room {

class RoomClient;

/**
 *  Listener class for room client
 *  Listens for room notifications from the server and calls relevant methods
 */
class RoomNotificationListener
{
public:
	RoomNotificationListener(const net::object::MetaClass &roomClass, const net::object::MetaClass &memberClass);
	virtual ~RoomNotificationListener();

	/**
	 *  Add the dispatcher and attach this listener's message handlers to it
	 *  @param	dispatcher	The message dispatcher containing the handlers
	 */
	virtual void AddMessageHandlers(core::message::DefaultParameterMessageDispatcherPtr dispatcher);

	/**
	 *  Remove message handlers
	 */
	virtual void RemoveMessageHandlers();

	/**
	 *  Called when a room join notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	virtual void OnRoomJoinNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomJoinNotificationPtr msg) = 0;

	/**
	 *  Called when a room leave notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	virtual void OnRoomLeaveNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomLeaveNotificationPtr msg) = 0;

	/**
	 *  Called when a room delete notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	virtual void OnRoomDeleteNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomDeleteNotificationPtr msg) = 0;

	/**
	 *  Called when a room set notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	virtual void OnRoomSetNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomSetNotificationPtr msg) = 0;

	/**
	 *  Called when a room join notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	virtual void OnRoomSetMemberNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomSetMemberNotificationPtr msg) = 0;

	/**
	 *  Called when a room relay notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	virtual void OnRoomRelayNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomRelayNotificationPtr msg) = 0;

	/**
	 *  Called when a room direct relay notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	virtual void OnRoomDirectRelayNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomDirectRelayNotificationPtr msg) = 0;
protected:

	/**
	 *  Add the default message handlers
	 */
	void AddDefaultMessageHandlers();

	/**
	 *  Remove the default message handlers
	 */
	void RemoveDefaultMessageHandlers();

	core::message::DefaultParameterMessageDispatcherPtr m_messageDispatcher;
	const net::object::MetaClass &m_roomClass;
	const net::object::MetaClass &m_memberClass;
};

/**
 *  The default room notification listener implementation
 */
class DefaultRoomNotificationListener : public RoomNotificationListener
{
public:
	DefaultRoomNotificationListener(RoomClient *roomClient);

	/**
	 *  Called when a room join notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	void OnRoomJoinNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomJoinNotificationPtr msg) override;

	/**
	 *  Called when a room leave notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	void OnRoomLeaveNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomLeaveNotificationPtr msg) override;

	/**
	 *  Called when a room delete notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	void OnRoomDeleteNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomDeleteNotificationPtr msg) override;

	/**
	 *  Called when a room set notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	void OnRoomSetNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomSetNotificationPtr msg) override;

	/**
	 *  Called when a room set member notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	void OnRoomSetMemberNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomSetMemberNotificationPtr msg) override;

	/**
	 *  Called when a room relay notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	void OnRoomRelayNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomRelayNotificationPtr msg) override;

	/**
	 *  Called when a room direct relay notification is received
	 *  @param	messageChannel	The message channel the message is received on
	 *  @param	msg	The notification message
	 */
	void OnRoomDirectRelayNotification(strix::net::message::MessageChannelPtr messageChannel, room::message::RoomDirectRelayNotificationPtr msg) override;
protected:
	RoomClient *m_roomClient;
};

typedef std::shared_ptr<RoomNotificationListener> RoomNotificationListenerPtr;

} } }
