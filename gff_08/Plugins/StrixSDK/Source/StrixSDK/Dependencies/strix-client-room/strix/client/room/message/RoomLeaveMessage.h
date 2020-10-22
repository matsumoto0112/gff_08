#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A request to leave a room
 *  
 *  Strix message type - Used for sending requests to the server
 */
class RoomLeaveMessage : public strix::client::core::message::ParameterRequestMessage
{
public:
	STRIX_CLASS(RoomLeaveMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomLeaveMessage")
		STRIX_PROPERTY(m_primaryKey)
	)

	RoomLeaveMessage() {}

	RoomLeaveMessage(const MetaClass &parameterClass) 
		: ParameterRequestMessage(parameterClass) {}

	RoomLeaveMessage(long long primaryKey) : m_primaryKey(primaryKey) {}

	RoomLeaveMessage(const MetaClass &parameterClass, long long primaryKey)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey) {}

	virtual ~RoomLeaveMessage() {}

	/**
	 *  Return the room id for the room that will be left
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the id representing the room that will be left
	 *  @param	primaryKey	The id of the room that will be left
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<RoomLeaveMessage> RoomLeaveMessagePtr;

} } } }
