#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace match { namespace room { namespace message {

/**
 *  Response to a successful kick request
 *  
 *  Strix response type - Received from server after request made
 */
class MatchRoomKickResponse : public strix::client::core::message::ParameterResponseMessage
{
public:
	STRIX_CLASS(MatchRoomKickResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.message.MatchRoomKickResponse")
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_kickedPlayerUid)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	MatchRoomKickResponse() {}

	virtual ~MatchRoomKickResponse() {}

	/**
	 *  Get the room id for the room the player was kicked from
	 *  @return	The room id
	 */
	long long GetRoomId() const {
		return m_roomId;
	}

	/**
	 *  Set the room id the player was kicked from
	 *  @param	roomId	The id
	 */
	void SetRoomId(long long roomId) {
		m_roomId = roomId;
	}

	/**
	 *  Get the UID of the kicked player
	 *  @returns	The UID
	 */
	const UIDPtr &GetKickedPlayerUid() const {
		return m_kickedPlayerUid;
	}

	/**
	 *  Set the UID of the kicked player
	 *  @param	kickedPlayerUid	The uid
	 */
	void SetKickedPlayerUid(const UIDPtr &kickedPlayerUid) {
		m_kickedPlayerUid = kickedPlayerUid;
	}

private:
	long long m_roomId;
	UIDPtr m_kickedPlayerUid;
};

typedef std::shared_ptr<MatchRoomKickResponse> MatchRoomKickResponsePtr;

} } } } }
