#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Request for information of members in the specified room
 *  
 *  Strix message type - Used for sending requests to the server
 */
class RoomGetMembersMessage : public strix::client::core::message::ParameterRequestMessage
{
public:
	STRIX_CLASS(RoomGetMembersMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomGetMembersMessage")
		STRIX_PROPERTY(m_primaryKey)
	)

	RoomGetMembersMessage() {}

	RoomGetMembersMessage(const MetaClass &parameterClass)
		: ParameterRequestMessage(parameterClass) {}

	RoomGetMembersMessage(long long primaryKey) : m_primaryKey(primaryKey) {}

	RoomGetMembersMessage(const MetaClass &parameterClass, long long primaryKey)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey) {}
	
	virtual ~RoomGetMembersMessage() {}

	/**
	 *  Return the room id the message will be sent to
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the room that the message will be sent to
	 *  @param	primaryKey	The room id of the room to send to
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<RoomGetMembersMessage> RoomGetMembersMessagePtr;

} } } }
