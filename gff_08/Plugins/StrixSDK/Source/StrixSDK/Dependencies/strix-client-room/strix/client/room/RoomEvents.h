#pragma once

#include <strix/client/core/NotificationEventArgs.h>

#include <functional>
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

namespace strix { namespace client { namespace room { namespace model {
class Room;
class RoomMember;
typedef std::shared_ptr<Room> RoomPtr;
typedef std::shared_ptr<RoomMember> RoomMemberPtr;
} } } }

namespace strix { namespace client { namespace room {

class RoomCreatedEventArgs
{
public:
	RoomCreatedEventArgs(model::RoomPtr room) : m_room(std::move(room)) {}

	model::RoomPtr GetRoom() const
	{
		return m_room;
	}

private:
	const model::RoomPtr m_room;
};

class RoomSetEventArgs
{
public:
	RoomSetEventArgs(model::RoomPtr room) : m_room(std::move(room)) {}

	model::RoomPtr GetRoom() const
	{
		return m_room;
	}

private:
	const model::RoomPtr m_room;
};

class RoomDeletedEventArgs
{
public:
	RoomDeletedEventArgs(model::RoomPtr room) : m_room(std::move(room)) {}

	model::RoomPtr GetRoom() const
	{
		return m_room;
	}

private:
	const model::RoomPtr m_room;
};

class RoomJoinedEventArgs
{
public:
	RoomJoinedEventArgs(model::RoomPtr room, model::RoomMemberPtr roomMember)
		: m_room(std::move(room)), m_roomMember(std::move(roomMember)) {}

	model::RoomPtr GetRoom() const
	{
		return m_room;
	}

	model::RoomMemberPtr GetRoomMember() const
	{
		return m_roomMember;
	}

private:
	const model::RoomPtr m_room;
	const model::RoomMemberPtr m_roomMember;
};

class RoomLeftEventArgs
{
public:
	RoomLeftEventArgs(model::RoomPtr room, model::RoomMemberPtr roomMember)
		: m_room(std::move(room)), m_roomMember(std::move(roomMember)) {}

	model::RoomPtr GetRoom() const
	{
		return m_room;
	}

	model::RoomMemberPtr GetRoomMember() const
	{
		return m_roomMember;
	}

private:
	const model::RoomPtr m_room;
	const model::RoomMemberPtr m_roomMember;
};

typedef std::function<void(RoomCreatedEventArgs)> RoomCreatedEventHandler;
typedef std::function<void(RoomSetEventArgs)> RoomSetEventHandler;
typedef std::function<void(RoomDeletedEventArgs)> RoomDeletedEventHandler;
typedef std::function<void(RoomJoinedEventArgs)> RoomJoinedEventHandler;
typedef std::function<void(RoomLeftEventArgs)> RoomLeftEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::RoomJoinNotificationPtr>)> RoomJoinNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::RoomLeaveNotificationPtr>)> RoomLeaveNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::RoomDeleteNotificationPtr>)> RoomDeleteNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::RoomSetNotificationPtr>)> RoomSetNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::RoomSetMemberNotificationPtr>)> RoomSetMemberNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::RoomRelayNotificationPtr>)> RoomRelayNotificationEventHandler;
typedef std::function<void(core::NotificationEventArgs<message::RoomDirectRelayNotificationPtr>)> RoomDirectRelayNotificationEventHandler;

} } }
