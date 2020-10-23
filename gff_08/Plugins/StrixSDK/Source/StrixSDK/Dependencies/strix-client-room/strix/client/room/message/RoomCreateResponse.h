#pragma once

#include <strix/client/core/message/CreateResponse.h>
#include <strix/client/room/model/RoomMember.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response to a successful room create request
 *  
 *  Strix response type - Received from server after request made
 */
class RoomCreateResponse : public strix::client::core::message::CreateResponse
{
public:
	STRIX_CLASS(RoomCreateResponse, CreateResponse)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomCreateResponse")
		STRIX_PROPERTY(m_roomMember)
	)
	
	typedef std::shared_ptr<strix::client::room::model::RoomMember> RoomMemberPtr;

	RoomCreateResponse() {}
	
	virtual ~RoomCreateResponse() {}

	/**
	 *  Get the room owner. If this response has just been received, the room owner
	 *  will likely be the player who requested the room be created
	 *  @returns	The room owner as a room member object
	 */
	const RoomMemberPtr &GetRoomMember() const {
		return m_roomMember;
	}

	/**
	 *  Set the room owner
	 *  @param	roomMember	The room member
	 */
	void SetRoomMember(const RoomMemberPtr &roomMember) {
		m_roomMember = roomMember;
	}

private:
	RoomMemberPtr m_roomMember;
};

typedef std::shared_ptr<RoomCreateResponse> RoomCreateResponsePtr;

} } } }
