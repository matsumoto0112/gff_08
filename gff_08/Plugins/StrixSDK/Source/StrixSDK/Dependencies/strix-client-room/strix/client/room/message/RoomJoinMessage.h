#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>

#include <map>
#include <utility>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A request to join a room
 *  
 *  Strix message type - Used for sending requests to the server
 */
class RoomJoinMessage : public strix::client::core::message::ParameterRequestMessage
{
public:
	STRIX_CLASS(RoomJoinMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomJoinMessage")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_roomMemberProperties)
	)
	
	RoomJoinMessage() {}

	RoomJoinMessage(long long primaryKey) : m_primaryKey(primaryKey) {}

	RoomJoinMessage(const MetaClass &parameterClass)
		: ParameterRequestMessage(parameterClass) {}

	RoomJoinMessage(const MetaClass &parameterClass, long long primaryKey)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey) {}

	RoomJoinMessage(const MetaClass &parameterClass, long long primaryKey, std::map<std::string, strix::net::object::ObjectPtr> roomMemberProperties)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey), m_roomMemberProperties(std::move(roomMemberProperties)) {}

	virtual ~RoomJoinMessage() = default;

	/**
	 *  Return the room id the message will be sent to
	 *  @returns	The room id
	 */
	long long GetPrimaryKey() const {
		return m_primaryKey;
	}

	/**
	 *  Set the room that the message will be sent to
	 *  @param	primaryKey	The room id of the room to send to
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Get the properties of the member joining the room
	 *  @returns	A map of string (property names) and objects (values)
	 */
	const std::map<std::string, strix::net::object::ObjectPtr> &GetRoomMemberProperties() const {
		return m_roomMemberProperties;
	}

	/*
	 *  Set the properties of the joining member
	 *  @param	roomMemberProperties	A map of string (property names) and objects (values)
	 */
	void SetRoomMemberProperties(const std::map<std::string, strix::net::object::ObjectPtr> &roomMemberProperties) {
		m_roomMemberProperties = roomMemberProperties;
	}

private:
	long long m_primaryKey;
	std::map<std::string, strix::net::object::ObjectPtr> m_roomMemberProperties;
};

typedef std::shared_ptr<RoomJoinMessage> RoomJoinMessagePtr;

} } } }
