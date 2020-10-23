#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response to a successful leave request
 *  
 *  Strix response type - Received from server after request made
 */
class RoomLeaveResponse : public strix::client::core::message::ParameterResponseMessage
{
public:
	STRIX_CLASS(RoomLeaveResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomLeaveResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	RoomLeaveResponse() {}

	RoomLeaveResponse(long long primaryKey) : m_primaryKey(primaryKey) {}
	
	virtual ~RoomLeaveResponse() {}

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

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<RoomLeaveResponse> RoomLeaveResponsePtr;

} } } }
