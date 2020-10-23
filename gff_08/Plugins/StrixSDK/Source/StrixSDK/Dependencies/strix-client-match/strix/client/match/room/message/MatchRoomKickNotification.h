#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/message/ParameterNotificationMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace match { namespace room { namespace message {

/**
 *  Notification that a player has been kicked
 *  
 *  Strix notification type - received when another player has performed some server action
 */
class MatchRoomKickNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(MatchRoomKickNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.message.MatchRoomKickNotification")
		STRIX_PROPERTY(m_roomId)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	MatchRoomKickNotification() {}

	MatchRoomKickNotification(const MetaClass &parameterClass)
		: ParameterNotificationMessage(parameterClass) {}

	MatchRoomKickNotification(const MetaClass &parameterClass, long long roomId)
		: ParameterNotificationMessage(parameterClass),
		  m_roomId(roomId) {}

	virtual ~MatchRoomKickNotification() {}

	/**
	 *  Get the room id the player was kicked from
	 *  @returns	The room id
	 */
	long long GetRoomId() const {
		return m_roomId;
	}

	/**
	 *  Set the room id the player was kicked from
	 *  @param	roomId	The id
	 */
	void SetRoomId(long long roomId) {
		m_roomId = roomId;
	}

private:
	long long m_roomId;
};

typedef std::shared_ptr<MatchRoomKickNotification> MatchRoomKickNotificationPtr;

} } } } }
