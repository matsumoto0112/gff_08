#pragma once

#include <strix/client/core/message/ParameterFailureMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response for a failed request to set a member's properties
 *  
 *  Strix response type - Received from server after request made
 */
class RoomSetMemberFailedResponse : public strix::client::core::message::ParameterFailureMessage
{
public:
	STRIX_CLASS(RoomSetMemberFailedResponse, ParameterFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomSetMemberFailedResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	RoomSetMemberFailedResponse() {}

	RoomSetMemberFailedResponse(long long primaryKey) : m_primaryKey(primaryKey) {}

	virtual ~RoomSetMemberFailedResponse() {}

	/**
	 *  Return the room id that the set was attempted on
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the room id that the set was attempted on
	 *  @returns	The room id
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<RoomSetMemberFailedResponse> RoomSetMemberFailedResponsePtr;

} } } }
