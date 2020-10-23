#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/message/DefaultNotificationMessage.h>
#include <strix/client/core/UID.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Notification received when a direct relay has been received. If you have received this,
 *  the message will be for you
 *  
 *  Strix notification type - Received when another player has performed some server action
 */
class RoomDirectRelayNotification : public strix::client::core::message::DefaultNotificationMessage
{
public:
	STRIX_CLASS(RoomDirectRelayNotification, DefaultNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomDirectRelayNotification")
		STRIX_PROPERTY(m_fromUid)
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_messageToRelay)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	RoomDirectRelayNotification() {}
		
	virtual ~RoomDirectRelayNotification() {}

	/**
	 *  Return the uid of the sender
	 *  @returns	The uid
	 */
	const UIDPtr &GetFromUid() const {
		return m_fromUid;
	}

	/**
	 *  Set the uid of the sender
	 *  @param	uid	The uid
	 */
	void SetFromUid(const UIDPtr &uid) {
		m_fromUid = uid;
	}

	/**
	 *  Return the room id this relay was sent to
	 *  @returns	The room id
	 */
	long long GetRoomId() {
		return m_roomId;
	}

	/**
	 *  Set the room to send to
	 *  @param	roomId	The room id
	 */
	void SetRoomId(long long roomId) {
		m_roomId = roomId;
	}

	/**
	 *  Return the relayed message
	 *  @returns	The relayed message
	 */
	const strix::net::object::ObjectPtr &GetMessageToRelay() const {
		return m_messageToRelay;
	}

	/**
	 *  Set the message to relay
	 *  @param	messageToRelay	The message to relay
	 */
	void SetMessageToRelay(const strix::net::object::ObjectPtr &messageToRelay) {
		m_messageToRelay = messageToRelay;
	}

private:
	UIDPtr m_fromUid;
	long long m_roomId;
	strix::net::object::ObjectPtr m_messageToRelay;
};

typedef std::shared_ptr<RoomDirectRelayNotification> RoomDirectRelayNotificationPtr;

} } } }
