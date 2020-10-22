#pragma once

#include <strix/client/room/model/Room.h>
#include <strix/client/room/model/RoomMember.h>
#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response to a successful room join request. If you are receiving this, the room member of this response
 *  will be you
 *  
 *  Strix response type - Received from server after request made
 */
class RoomJoinResponse : public strix::client::core::message::ParameterResponseMessage
{
public:
	STRIX_CLASS(RoomJoinResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomJoinResponse")
		STRIX_PROPERTY(m_room)
		STRIX_PROPERTY(m_joinedMember)
		STRIX_PROPERTY(m_otherRoomMembers)
	)

	typedef strix::net::object::MetaClass MetaClass;
	typedef strix::client::room::model::RoomPtr RoomPtr;
	typedef strix::client::room::model::RoomMemberPtr RoomMemberPtr;

	RoomJoinResponse(): ParameterResponseMessage(2) {}

	RoomJoinResponse(RoomPtr room) : ParameterResponseMessage(2), m_room(room) {}
	
	virtual ~RoomJoinResponse() {}

	/**
	 *  Return the room object representing the room joined
	 *  @returns	The room
	 */
	const RoomPtr &GetRoom() {
		return m_room;
	}

	/**
	 *  Set the room object representing the room joined
	 *  @param	room	The room
	 */
	void SetRoom(const RoomPtr &room) {
		m_room = room;
	}

	/**
	 *  Get the meta class of the room member
	 *  @returns	The meta class
	 */
	const strix::net::object::MetaClass &GetRoomMemberClass() const {
        return GetParameterClass(1);
    }

	/**
	 *  Set the meta class of the room member
	 *  @
	 */
    void SetRoomMemberClass(const strix::net::object::MetaClass &roomMemberClass) {
		SetParameterClass(1, roomMemberClass);
    }

	/**
	 *  Return the room member that joined the room. If you are receiving this response,
	 *  this will likely be you
	 *  @returns	The joined member
	 */
	const RoomMemberPtr &GetJoinedMember() const {
		return m_joinedMember;
	}

	/**
	 *  Set the joined member
	 *  @param	joinedMember	The joined member
	 */
	void SetJoinedMember(const RoomMemberPtr &joinedMember) {
		m_joinedMember = joinedMember;
	}

	/**
	 *  Get a list of the other room members in the room, excluding the newly joined member
	 *  @returns	The list of other members
	 */
	strix::net::object::ObjectList &GetRoomMembers() {
		return m_otherRoomMembers;
	}

	/**
	 *  Set the other room members
	 *  @param	otherRoomMembers	The other members
	 */
	void SetRoomMembers(const strix::net::object::ObjectList &otherRoomMembers) {
		m_otherRoomMembers = otherRoomMembers;
	}

private:
	RoomPtr m_room;
	RoomMemberPtr m_joinedMember;
	strix::net::object::ObjectList m_otherRoomMembers;
};

typedef std::shared_ptr<RoomJoinResponse> RoomJoinResponsePtr;

} } } }
