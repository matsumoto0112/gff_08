#pragma once

#include <strix/client/core/message/ParameterMessage.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/message/DefaultNotificationMessage.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Notification that a player has set the properties of a room
 *
 *  Strix notification type - Received when another player has performed some server action
 */
class RoomSetNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(RoomSetNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomSetNotification")
		STRIX_PROPERTY(m_room)
	)

	RoomSetNotification() {}

	RoomSetNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	virtual ~RoomSetNotification() {}

	/**
	 *  Return the room set
	 *  @returns	The room
	 */
	const strix::net::object::ObjectPtr &GetRoom() const {
		return m_room;
	}

	/**
	 *  Set the room set
	 *  @param	room	The room
	 */
	void SetRoom(const strix::net::object::ObjectPtr &room) {
		m_room = room;
	}

private:
	strix::net::object::ObjectPtr m_room;
};

typedef std::shared_ptr<RoomSetNotification> RoomSetNotificationPtr;

} } } }
