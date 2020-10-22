#pragma once

#include <strix/client/core/message/ParameterNotificationMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Notification received when a room has been deleted
 *  
 *  Strix notification type - Received when another player has performed some server action
 */
class RoomDeleteNotification : public strix::client::core::message::ParameterNotificationMessage
{
public:
	STRIX_CLASS(RoomDeleteNotification, ParameterNotificationMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomDeleteNotification")
		STRIX_PROPERTY(m_primaryKey)
	)

	RoomDeleteNotification() {}

	RoomDeleteNotification(const MetaClass &parameterClass) : ParameterNotificationMessage(parameterClass) {}

	RoomDeleteNotification(long long primaryKey) : m_primaryKey(primaryKey) {}

	RoomDeleteNotification(const MetaClass &parameterClass, long long primaryKey)
		: ParameterNotificationMessage(parameterClass), m_primaryKey(primaryKey) {}

	virtual ~RoomDeleteNotification() {}

	/**
	 *  Get the primary key for the room that was deleted
	 *  @returns	The key
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the primary key for the room that was deleted
	 *  @param	primaryKey	The key
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<RoomDeleteNotification> RoomDeleteNotificationPtr;

} } } }
