#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response to a successful request for information about room members
 *  
 *  Strix response type - Received from server after request made
 */
class RoomGetMembersResponse : public strix::client::core::message::ParameterResponseMessage
{
public:
	STRIX_CLASS(RoomGetMembersResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomGetMembersResponse")
		STRIX_PROPERTY(m_memberCollection)
	)

	RoomGetMembersResponse() {}
	
	virtual ~RoomGetMembersResponse() {}

	/**
	 *  Return the members of the room as a list
	 *  @returns	A list of objects representing the room members
	 */
	strix::net::object::ObjectList &GetMemberCollection() {
		return m_memberCollection;
	}

	/**
	 *  Set the members of the room 
	 *  @param	memberCollection	The list of members
	 */
	void SetMemberCollection(const strix::net::object::ObjectList &memberCollection) {
		m_memberCollection = memberCollection;
	}

private:
	strix::net::object::ObjectList m_memberCollection;
};

typedef std::shared_ptr<RoomGetMembersResponse> RoomGetMembersResponsePtr;

} } } }
