#pragma once

#include <strix/client/core/message/ParameterMessage.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/room/model/RoomMember.h>
#include <strix/client/core/UID.h>

namespace strix { namespace client { namespace match { namespace room { namespace model {

/**
 *  Model of a match room member, a room member currently in a match
 */
class MatchRoomMember : public strix::client::room::model::RoomMember
{
public:
	STRIX_CLASS(MatchRoomMember, RoomMember)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.model.MatchRoomMember")
		STRIX_PROPERTY(m_uid)
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_name)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;
	
	MatchRoomMember() {}
	
	virtual ~MatchRoomMember() {}

	/**
	 *  Return this member's primary key
	 *  @returns	The key
	 */
	long long GetPrimaryKey() const override {
		return m_primaryKey;
	}

	/**
	 *  Set this member's primary key
	 *  @param	primaryKey	The key
	 */
	void SetPrimaryKey(long long primaryKey) override {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Get this members uid
	 *  @returns	The UID
	 */
	const UIDPtr &GetUid() const override {
		return m_uid;
	}

	/**
	 *  Set this members uid
	 *  @param	uid	The UID
	 */
	void SetUid(const UIDPtr &uid) override {
		m_uid = uid;
	}

	/**
	 *  Get the room id this member belongs to
	 *  @returns	The room id
	 */
	long long GetRoomId() const override {
		return m_roomId;
	}

	/**
	 *  Set the room id this member belongs to
	 *  @param	roomId	The room id
	 */
	void SetRoomId(long long roomId) override {
		m_roomId = roomId;
	}

	/**
	 *  Get the name of this member
	 *  @returns	The name
	 */
	const std::string &GetName() const {
		return m_name;
	}

	/**
	 *  Set the name of this member
	 *  @param	name	The name
	 */
	void SetName(const std::string &name) {
		m_name = name;
	}

private:
	long long m_primaryKey;
	UIDPtr m_uid;
	long long m_roomId;
	std::string m_name;
};

typedef std::shared_ptr<MatchRoomMember> MatchRoomMemberPtr;

} } } } }
