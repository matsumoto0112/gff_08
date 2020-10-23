#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/message/ParameterRequestMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace match { namespace room { namespace message {

/**
 *  Request to kick a player
 *  
 *  Strix message type - Used for sending requests to the server
 */
class MatchRoomKickMessage : public strix::client::core::message::ParameterRequestMessage
{
public:
	STRIX_CLASS(MatchRoomKickMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.message.MatchRoomKickMessage")
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_kickedPlayerUid)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	MatchRoomKickMessage() {}

	MatchRoomKickMessage(long long roomId, const UIDPtr &kickedPlayerUid)
		: m_roomId(roomId), m_kickedPlayerUid(kickedPlayerUid) {}

	MatchRoomKickMessage(const MetaClass &parameterClass)
		: ParameterRequestMessage(parameterClass) {}

	MatchRoomKickMessage(const MetaClass &parameterClass, long long roomId, const UIDPtr &kickedPlayerUid)
		: ParameterRequestMessage(parameterClass), m_roomId(roomId), m_kickedPlayerUid(kickedPlayerUid) {}

	virtual ~MatchRoomKickMessage() {}

	/**
	 *  Get the room id to kick from
	 *  @returns	The room id
	 */
	long long GetRoomId() const {
		return m_roomId;
	}

	/**
	 *  Set the room id to kick from
	 *  @param	roomId	The room id
	 */
	void SetRoomId(long long roomId) {
		m_roomId = roomId;
	}

	/**
	 *  Get the uid of the player to kick
	 *  @returns	The uid
	 */
	const UIDPtr &GetKickedPlayerUid() const {
		return m_kickedPlayerUid;
	}

	/**
	 *  Set the player to kick
	 *  @param	kickedPlayerUid	The player's uid
	 */
	void SetKickedPlayerUid(const UIDPtr &kickedPlayerUid) {
		m_kickedPlayerUid = kickedPlayerUid;
	}

private:
	long long m_roomId;
	UIDPtr m_kickedPlayerUid;
};

typedef std::shared_ptr<MatchRoomKickMessage> MatchRoomKickMessagePtr;

} } } } }
