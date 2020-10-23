#pragma once

#include <strix/client/room/model/RoomMember.h>
#include <strix/client/core/message/ParameterNotificationMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Notification received when a player has left a room
 *  
 *  Strix notification type - Received when another player has performed some server action
 */
class RoomLeaveNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(RoomLeaveNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomLeaveNotification")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_goneMember)
	)
	
	typedef std::shared_ptr<strix::client::room::model::RoomMember> RoomMemberPtr;

	RoomLeaveNotification() {}

	RoomLeaveNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	virtual ~RoomLeaveNotification() {}

	/**
	 *  Return the room id for the room that was left
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the id representing the room that was left
	 *  @param	primaryKey	The id of the room that was left
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Return the member that left the room
	 *  @returns	The member
	 */
	const RoomMemberPtr &GetGoneMember() const {
		return m_goneMember;
	}

	/**
	 *  Set the member that left the room
	 *  @param	goneMember	The member that left
	 */
	void SetGoneMember(const RoomMemberPtr &goneMember) {
		m_goneMember = goneMember;
	}

private:
	long long m_primaryKey;
	RoomMemberPtr m_goneMember;
};

typedef std::shared_ptr<RoomLeaveNotification> RoomLeaveNotificationPtr;

} } } }
