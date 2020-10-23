#pragma once

#include <strix/client/core/UID.h>
#include <strix/client/core/model/Model.h>

namespace strix { namespace client { namespace node { namespace model {

/**
 *  Model of the master server's information about a room
 */
class NodeRoom : public strix::client::core::model::Model
{
public:
	STRIX_ABSTRACT_CLASS(NodeRoom, Model)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.node.model.NodeRoom")
		STRIX_PROPERTY(m_nodeUid)
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_capacity)
		STRIX_PROPERTY(m_memberCount)
	)
	
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	NodeRoom() {}

	virtual ~NodeRoom() {}

	/**
	 *  Return the primary key
	 *  @returns	key
	 */
	long long GetPrimaryKey() const override = 0;

	/**
	 *  Set the primary key
	 *  @param	id	key
	 */
	void SetPrimaryKey(long long id) override = 0;

	/**
	 *  Return the uid of the node object
	 *  @returns	The UID of the node
	 */
	virtual const UIDPtr &GetNodeUid() const {
		return m_nodeUid;
	}

	/**
	 *  Set the node object's uid
	 *  @param	nodeUid	The UID
	 */
	virtual void SetNodeUid(const UIDPtr &nodeUid) {
		m_nodeUid = nodeUid;
	}

	/**
	 *  Get the uid of the room object
	 *  @returns	The uid
	 */
	virtual long long GetRoomId() {
		return m_roomId;
	}

	/**
	 *  Set the uid of the room object
	 *  @param	roomId	The uid
	 */
	virtual void SetRoomId(long long roomId) {
		m_roomId = roomId;
	}

	/**
	 *  Get the capacity the room supports
	 *  @returns	The capacity
	 */
	virtual int GetCapacity() {
		return m_capacity;
	}

	/**
	 *  Set the capacity this room supports
	 *  @param	capacity	The capacity
	 */
	virtual void SetCapacity(int capacity) {
		m_capacity = capacity;
	}

	/**
	 *  Get the current number of players in the room
	 *  @returns	The number of players
	 */
	virtual int GetMemberCount() {
		return m_memberCount;
	}

	/**
	 *  Set the number of members in the room
	 *  @param	memberCount	The number of members
	 */
	virtual void SetMemberCount(int memberCount) {
		m_memberCount = memberCount;
	}

private:
	UIDPtr m_nodeUid;
	long long m_roomId;
	int m_capacity;
	int m_memberCount;
};

} } } }
