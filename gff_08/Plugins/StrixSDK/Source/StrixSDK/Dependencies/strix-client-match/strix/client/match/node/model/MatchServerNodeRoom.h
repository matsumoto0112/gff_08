#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/model/Model.h>
#include <strix/client/node/model/NodeRoom.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace match { namespace node { namespace model {

/**
 *  An implementation of NodeRoom for matches
 */
class MatchServerNodeRoom : public strix::client::node::model::NodeRoom
{
public:
	STRIX_CLASS(MatchServerNodeRoom, NodeRoom)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.node.model.MatchServerNodeRoom")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_isPasswordProtected)
		STRIX_PROPERTY(m_isJoinable)
		STRIX_PROPERTY(m_state)
		STRIX_PROPERTY(m_name)
	)

	typedef std::shared_ptr<strix::net::object::StringObject> StringPtr;

	MatchServerNodeRoom() {}

	virtual ~MatchServerNodeRoom() {}

	/**
	 *  Get this room's primary key
	 *  @returns	key
	 */
	long long GetPrimaryKey() const override {
		return m_primaryKey;
	}

	/**
	 *  Set this room's primary key
	 *  @param	id	key
	 */
	void SetPrimaryKey(long long id) override {
		m_primaryKey = id;
	}

	/**
	 *  Get if this room is password protected
	 *  @returns	True if this room is password protected
	 */
	virtual bool GetIsPasswordProtected() {
		return m_isPasswordProtected;
	}

	/**
	 *  Set the password protected status of this room
	 *  @param	isPasswordProtected	The status
	 */
	virtual void SetIsPasswordProteced(bool isPasswordProtected) {
		m_isPasswordProtected = isPasswordProtected;
	}

	/**
	 *  Get if this room is joinable
	 *  @returns	True if this room is joinable
	 */
	virtual bool GetIsJoinable() {
		return m_isJoinable;
	}

	/**
	 *  Set the joinable state of this room
	 *  @param	isJoinable	The status
	 */
	virtual void SetIsJoinable(bool isJoinable) {
		m_isJoinable = isJoinable;
	}

	/**
	 *  Get the state of this room
	 *  @returns	state
	 */
	virtual int GetState() {
		return m_state;
	}

	/**
	 *  Set the state of this room
	 *  @param	state	The state
	 */
	virtual void SetState(int state) {
		m_state = state;
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

private:
	long long m_primaryKey;
	bool m_isPasswordProtected;
	bool m_isJoinable;
	int m_state;
	StringPtr m_name;
};

} } } } }
