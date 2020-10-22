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

namespace strix { namespace client { namespace match { namespace room { namespace message {
class MatchRoomKickNotification;
typedef std::shared_ptr<MatchRoomKickNotification> MatchRoomKickNotificationPtr;
} } } } }

namespace strix { namespace client { namespace match {

class MatchRoomClient;

/**
 *  Abstract notification listener class for match rooms
 */
class MatchRoomNotificationListener
{
public:
	MatchRoomNotificationListener(const net::object::MetaClass &roomClass);
	virtual ~MatchRoomNotificationListener();

	/**
	 *  Add the dispatcher and attach this listener's handlers to it
	 *  @param	dispatcher	The dispatcher containing the message handlers
	 */
	virtual void AddMessageHandlers(core::message::DefaultParameterMessageDispatcherPtr dispatcher);

	/**
	 *  Remove the message handlers
	 */
	virtual void RemoveMessageHandlers();

	/**
	 *  Called when we receive notification that a player was kicked from a match
	 *  @param	messageChannel	The channel the notification was received from
	 *  @param	msg	The message containing the notification data
	 */
	virtual void OnMatchRoomKickNotification(strix::net::message::MessageChannelPtr messageChannel, match::room::message::MatchRoomKickNotificationPtr msg) = 0;

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
	const net::object::MetaClass &m_roomClass;
};

/**
 *  The default match room notification listener class
 */
class DefaultMatchRoomNotificationListener : public MatchRoomNotificationListener
{
public:
	DefaultMatchRoomNotificationListener(MatchRoomClient *matchRoomClient);

	/**
	 *  Called when we receive notification that a player was kicked from a match
	 *  @param	messageChannel	The channel the notification was received from
	 *  @param	msg	The message containing the notification data
	 */
	void OnMatchRoomKickNotification(strix::net::message::MessageChannelPtr messageChannel, match::room::message::MatchRoomKickNotificationPtr msg) override;
protected:

	MatchRoomClient *m_matchRoomClient;
};

typedef std::shared_ptr<MatchRoomNotificationListener> MatchRoomNotificationListenerPtr;

} } }
