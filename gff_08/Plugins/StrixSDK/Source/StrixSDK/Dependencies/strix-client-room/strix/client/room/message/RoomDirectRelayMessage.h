#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/message/DefaultRequestMessage.h>
#include <strix/client/core/UID.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A request to relay a direct message
 *  
 *  Strix message type - Used for sending requests to the server
 */
class RoomDirectRelayMessage : public strix::client::core::message::DefaultRequestMessage
{
public:
	STRIX_CLASS(RoomDirectRelayMessage, DefaultRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomDirectRelayMessage")
		STRIX_PROPERTY(m_to)
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_messageToRelay)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	RoomDirectRelayMessage() {}
		
	virtual ~RoomDirectRelayMessage() {}

	/**
	 *  Return the uid of the intended recipient
	 *  @returns	The uid
	 */
	const UIDPtr &GetTo() const {
		return m_to;
	}

	/**
	 *  Set the intended recipient
	 *  @param	to	The uid of the recipient
	 */
	void SetTo(const UIDPtr &to) {
		m_to = to;
	}

	/**
	 *  Return the room id the message will be sent to
	 *  @returns	The room id
	 */
	long long GetRoomId() {
		return m_roomId;
	}

	/**
	 *  Set the room that the message will be sent to
	 *  @param	roomId	The room id of the room to send to
	 */
	void SetRoomId(long long roomId) {
		m_roomId = roomId;
	}

	/**
	 *  Return the message that will be relayed
	 *  @returns	The message object
	 */
	const strix::net::object::ObjectPtr &GetMessageToRelay() const {
		return m_messageToRelay;
	}

	/**
	 *  Set the message to relay
	 *  @param	messageToRelay	The relay message
	 */
	void SetMessageToRelay(const strix::net::object::ObjectPtr &messageToRelay) {
		m_messageToRelay = messageToRelay;
	}

private:
	UIDPtr m_to;
	long long m_roomId;
	strix::net::object::ObjectPtr m_messageToRelay;
};

typedef std::shared_ptr<RoomDirectRelayMessage> RoomDirectRelayMessagePtr;

} } } }
