#pragma once

#include <strix/client/core/message/CreateMessage.h>

#include <map>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Message for creating a room
 *  
 *  Strix message type - Used for sending requests to the server
 */
class RoomCreateMessage : public strix::client::core::message::CreateMessage
{
public:
	STRIX_CLASS(RoomCreateMessage, CreateMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomCreateMessage")
		STRIX_PROPERTY(m_roomMemberProperties)
		STRIX_PROPERTY(m_joinImmediately)
	)

	RoomCreateMessage() : m_joinImmediately(true) {}

	RoomCreateMessage(const MetaClass &parameterClass) 
		: CreateMessage(parameterClass), m_joinImmediately(true) {}

	RoomCreateMessage(const std::map<std::string, strix::net::object::ObjectPtr> &initialProperties)
		: CreateMessage(initialProperties), m_joinImmediately(true) {}

	RoomCreateMessage(const MetaClass &parameterClass, const std::map<std::string, strix::net::object::ObjectPtr> &initialProperties)
		: CreateMessage(parameterClass, initialProperties), m_joinImmediately(true) {}

	virtual ~RoomCreateMessage() = default;

	/**
	 *  Return the properties of the room owner
	 *  @returns	A map of strings (property names) to objects (values)
	 */
	const std::map<std::string, strix::net::object::ObjectPtr> &GetRoomMemberProperties() const {
		return m_roomMemberProperties;
	}

	/**
	 *  Set the properties for the room owner. The player who sends this message with be the first player
	 *  in the room and therefore the room owner.
	 *  @param	roomMemberProperties	A map of strings (property names) to objects (values)
	 */
	void SetRoomMemberProperties(const std::map<std::string, strix::net::object::ObjectPtr> &roomMemberProperties) {
		m_roomMemberProperties = roomMemberProperties;
	}

	/**
	 *  Get the join immediately value
	 *  @returns	True if set to join immediately, else false
	 */
	bool GetJoinImmediately() const {
		return m_joinImmediately;
	}

	/**
	 *  Set the join immediately value (whether to join the room immediately after creation or not)
	 *  @param	joinImmediately	The value
	 */
	void SetJoinImmediately(bool joinImmediately) {
		m_joinImmediately = joinImmediately;
	}

private:
	std::map<std::string, strix::net::object::ObjectPtr> m_roomMemberProperties;
	bool m_joinImmediately;
};

typedef std::shared_ptr<RoomCreateMessage> RoomCreateMessagePtr;

} } } }
