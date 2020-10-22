#pragma once

#include <strix/client/core/message/ParameterFailureMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response to a failed leave request
 *  
 *  Strix response type - Received from server after request made
 */
class RoomLeaveFailedResponse : public strix::client::core::message::ParameterFailureMessage
{
public:
	STRIX_CLASS(RoomLeaveFailedResponse, ParameterFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomLeaveFailedResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	RoomLeaveFailedResponse() {}

	RoomLeaveFailedResponse(long long primaryKey) : m_primaryKey(primaryKey) {}
	
	virtual ~RoomLeaveFailedResponse() {}

	/**
	 *  Return the room id
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the room id
	 *  @param	primaryKey	The room id
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<RoomLeaveFailedResponse> RoomLeaveFailedResponsePtr;

} } } }
