#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/message/ParameterFailureMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace match { namespace room { namespace message {

/**
 *  Response to a failed kick request
 *  
 *  Strix response type - Received from server after request made
 */
class MatchRoomKickFailedResponse : public strix::client::core::message::ParameterFailureMessage
{
public:
	STRIX_CLASS(MatchRoomKickFailedResponse, ParameterFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.message.MatchRoomKickFailedResponse")
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_kickedPlayerUid)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	MatchRoomKickFailedResponse() {}
	
	virtual ~MatchRoomKickFailedResponse() {}

	/**
	 *  Get the attempted room id to kick from
	 *  @returns	The room id
	 */
	long long GetRoomId() const {
		return m_roomId;
	}

	/**
	 *  Set the attempted room id to kick from
	 *  @param	roomId	The room id
	 */
	void SetRoomId(long long roomId) {
		m_roomId = roomId;
	}

	/**
	 *  Get the player that we tried to kick
	 *  @returns	The player's uid
	 */
	const UIDPtr &GetKickedPlayerUid() const {
		return m_kickedPlayerUid;
	}

	/**
	 *  Set the player uid that we tried to kick
	 *  @param	kickedPlayerUid	The player's uid
	 */
	void SetKickedPlayerUid(const UIDPtr &kickedPlayerUid) {
		m_kickedPlayerUid = kickedPlayerUid;
	}

private:
	long long m_roomId;
	UIDPtr m_kickedPlayerUid;
};

typedef std::shared_ptr<MatchRoomKickFailedResponse> MatchRoomKickFailedResponsePtr;

} } } } }
