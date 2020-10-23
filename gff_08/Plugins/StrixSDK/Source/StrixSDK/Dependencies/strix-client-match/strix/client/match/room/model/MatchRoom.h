#pragma once

#include <strix/client/core/message/ParameterMessage.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/room/model/Room.h>
#include <strix/client/core/UID.h>

namespace strix { namespace client { namespace match { namespace room { namespace model {

/**
 *  Model class for storing information about a match room
 */
class MatchRoom : public strix::client::room::model::Room
{
public:
	STRIX_CLASS(MatchRoom, Room)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.model.MatchRoom")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_ownerUid)
		STRIX_PROPERTY(m_name)
		STRIX_PROPERTY(m_capacity)
		STRIX_PROPERTY(m_memberCount)
		STRIX_PROPERTY(m_password)
		STRIX_PROPERTY(m_state)
		STRIX_PROPERTY(m_isJoinable)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;
	typedef std::shared_ptr<strix::net::object::StringObject> StringPtr;
	
	MatchRoom() {}

	virtual ~MatchRoom() {}

	/**
	 *  Return this room's primary key
	 *  @returns	The key
	 */
	long long GetPrimaryKey() const override {
		return m_primaryKey;
	}

	/**
	 *  Set this room's primary key
	 *  @param	primaryKey	The key
	 */
	void SetPrimaryKey(long long primaryKey) override {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Get this room's owner's uid
	 *  @returns	The UID
	 */
	const UIDPtr &GetOwnerUid() const {
		return m_ownerUid;
	}

	/**
	 *  Set this room's owners' uid
	 *  @param	ownerUid	The UID
	 */
	void SetOwnerUid(const UIDPtr &ownerUid) {
		m_ownerUid = ownerUid;
	}

	/**
	 *  Get the name of this room
	 *  @returns	The name
	 */
	const StringPtr &GetName() const {
		return m_name;
	}

	/**
	 *  Set the name of this room
	 *  @param	name	The name
	 */
	void SetName(const StringPtr &name) {
		m_name = name;
	}

	/**
	 *  Return the max capacity of this room
	 *  @returns	The capacity
	 */
	int GetCapacity() const {
		return m_capacity;
	}

	/**
	 *  Set the max capacity of this room
	 *  @param	capacity	The capacity
	 */
	void SetCapacity(int capacity) {
		m_capacity = capacity;
	}

	/**
	 *  Get the current count of members in this room
	 *  @returns	The count
	 */
	int GetMemberCount() const {
		return m_memberCount;
	}

	/**
	 *  Set the number of members in this room
	 *  @param	memberCount	The number of members
	 */
	void SetMemberCount(int memberCount) {
		m_memberCount = memberCount;
	}

	/**
	 *  Return this room's password
	 *  @returns	The password
	 */
	const StringPtr &GetPassword() const {
		return m_password;
	}

	/**
	 *  Set the password for this room
	 *  @param	password	The password
	 */
	void SetPassword(const StringPtr &password) {
		m_password = password;
	}

	/**
	 *  Get the room's current state
	 *  @returns	The state
	 */
	int GetState() const {
		return m_state;
	}

	/**
	 *  Set this room's state
	 *  @param	state	The state
	 */
	void SetState(int state) {
		m_state = state;
	}

	/**
	 *  Return true if the room is joinable
	 *  @returns	Whether the room is joinable
	 */
	bool GetIsJoinable() const {
		return m_isJoinable;
	}

	/**
	 *  Set the is joinable state
	 *  @param	isJoinable	true or false
	 */
	void SetIsJoinable(bool isJoinable) {
		m_isJoinable = isJoinable;
	}

private:
	long long m_primaryKey;
	UIDPtr m_ownerUid;
	StringPtr m_name;
	int m_capacity;
	int m_memberCount;
	StringPtr m_password;
	int m_state;
	bool m_isJoinable;
};

typedef std::shared_ptr<MatchRoom> MatchRoomPtr;

} } } } }
