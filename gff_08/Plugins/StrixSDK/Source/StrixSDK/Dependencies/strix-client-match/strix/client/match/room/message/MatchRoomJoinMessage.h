#pragma once

#include <strix/client/room/message/RoomJoinMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace match { namespace room { namespace message {

/**
 *  Used for sending a match room join request
 *  
 *  Strix message type - Used for sending requests to the server
 */
class MatchRoomJoinMessage : public strix::client::room::message::RoomJoinMessage
{
public:
	STRIX_CLASS(MatchRoomJoinMessage, RoomJoinMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.message.MatchRoomJoinMessage")
		STRIX_PROPERTY(m_password)
	)
	
	typedef std::shared_ptr<strix::net::object::StringObject> StringPtr;

	MatchRoomJoinMessage() {}

	MatchRoomJoinMessage(long long primaryKey)
		: RoomJoinMessage(primaryKey) {}

	MatchRoomJoinMessage(const MetaClass &parameterClass)
		: RoomJoinMessage(parameterClass) {}

	MatchRoomJoinMessage(const MetaClass &parameterClass, long long primaryKey)
		: RoomJoinMessage(parameterClass, primaryKey) {}

	MatchRoomJoinMessage(const MetaClass &parameterClass, long long primaryKey, const std::map<std::string, strix::net::object::ObjectPtr> &roomMemberProperties)
		: RoomJoinMessage(parameterClass, primaryKey, roomMemberProperties) {}

	virtual ~MatchRoomJoinMessage() {}

	/**
	 *  Get the password we will use
	 *  @returns	The password
	 */
	const StringPtr &GetPassword() const {
		return m_password;
	}

	/**
	 *  Set the password to use
	 *  @param	password	The password
	 */
	void SetPassword(const StringPtr &password) {
		m_password = password;
	}

private:
	StringPtr m_password;
};

typedef std::shared_ptr<MatchRoomJoinMessage> MatchRoomJoinMessagePtr;

} } } } }
