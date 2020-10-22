#pragma once

#include <strix/client/room/model/RoomMember.h>
#include <strix/client/core/message/ParameterNotificationMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Notification received when a player has joined a room
 *  
 *  Strix notification type - Received when another player has performed some server action
 */
class RoomJoinNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(RoomJoinNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomJoinNotification")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_newlyJoinedMember)
	)
	
	typedef std::shared_ptr<strix::client::room::model::RoomMember> RoomMemberPtr;

	RoomJoinNotification() {}

	RoomJoinNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	virtual ~RoomJoinNotification() {}

	/**
	 *  The id of the room joined
	 *  @returns	The id
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the id of the room joined
	 *  @param	primaryKey	The id
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Get the room member that joined the room
	 *  @returns	The room member
	 */
	const RoomMemberPtr &GetNewlyJoinedMember() const {
		return m_newlyJoinedMember;
	}

	/**
	 *  Set the room member that joined the room
	 *  @param	newlyJoinedMember	The member
	 */
	void SetNewlyJoinedMember(const RoomMemberPtr &newlyJoinedMember) {
		m_newlyJoinedMember = newlyJoinedMember;
	}

private:
	long long m_primaryKey;
	RoomMemberPtr m_newlyJoinedMember;
};

typedef std::shared_ptr<RoomJoinNotification> RoomJoinNotificationPtr;

} } } }
