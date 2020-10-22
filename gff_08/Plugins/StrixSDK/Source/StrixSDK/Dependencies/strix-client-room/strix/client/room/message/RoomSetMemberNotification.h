#pragma once

#include <strix/client/core/message/ParameterNotificationMessage.h>
#include <strix/client/room/model/RoomMember.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Notification received when a player has set the properties of a room member
 *
 *  Strix notification type - Received when another player has performed some server action
 */
class RoomSetMemberNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(RoomSetMemberNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomSetMemberNotification")
		STRIX_PROPERTY(m_member)
	)

    typedef std::shared_ptr<strix::client::room::model::RoomMember> RoomMemberPtr;

	RoomSetMemberNotification() {}

	RoomSetMemberNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	RoomSetMemberNotification(const RoomMemberPtr &member) : m_member(member) {}

	virtual ~RoomSetMemberNotification() {}

	/**
	 *  Get the member whose properties were set
	 *  @returns	The member
	 */
	const RoomMemberPtr &GetMember() const {
		return m_member;
	}

	/**
	 *  Set the member whose properties were set
	 *  @param	member	The member
	 */
	void SetMember(const RoomMemberPtr &member) {
		m_member = member;
	}

private:
	RoomMemberPtr m_member;
};

typedef std::shared_ptr<RoomSetMemberNotification> RoomSetMemberNotificationPtr;

} } } }
