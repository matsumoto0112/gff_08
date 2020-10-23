#pragma once

#include <strix/client/core/message/ParameterFailureMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response to a failed room join request
 *  
 *  Strix response type - Received from server after request made
 */
class RoomJoinFailedResponse : public strix::client::core::message::ParameterFailureMessage
{
public:
	STRIX_CLASS(RoomJoinFailedResponse, ParameterFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomJoinFailedResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	RoomJoinFailedResponse() {}

	RoomJoinFailedResponse(long long primaryKey) : m_primaryKey(primaryKey) {}
	
	virtual ~RoomJoinFailedResponse() {}

	/**
	 *  Return the room id this join was sent to
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the room id 
	 *  @param	primaryKey	The id
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<RoomJoinFailedResponse> RoomJoinFailedResponsePtr;

} } } }
