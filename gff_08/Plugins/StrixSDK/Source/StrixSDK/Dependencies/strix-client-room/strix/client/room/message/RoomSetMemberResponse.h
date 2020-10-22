#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A successful response to a request to set member properties
 *  
 *  Strix response type - Received from server after request made
 */
class RoomSetMemberResponse : public strix::client::core::message::ParameterResponseMessage
{
public:
	STRIX_CLASS(RoomSetMemberResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomSetMemberResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	RoomSetMemberResponse() {}

	RoomSetMemberResponse(long long primaryKey) : m_primaryKey(primaryKey) {}

	virtual ~RoomSetMemberResponse() {}

	/**
	 *  Return the room id this set member was sent to
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the room 
	 *  @param	primaryKey	The room id of the room to send to
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<RoomSetMemberResponse> RoomSetMemberResponsePtr;

} } } }
