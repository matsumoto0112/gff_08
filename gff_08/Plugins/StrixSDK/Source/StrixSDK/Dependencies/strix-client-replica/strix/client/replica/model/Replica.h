#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/UID.h>

namespace strix { namespace client { namespace replica { namespace model {

/**
 *  A model of a replica
 */
class Replica : public strix::net::object::Object
{
public:
	STRIX_CLASS(Replica, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.replica.model.Replica")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_objectType)
		STRIX_PROPERTY(m_roomId)
		STRIX_PROPERTY(m_ownerUid)
		STRIX_PROPERTY(m_properties)
	)

	Replica() {}

	virtual ~Replica() {}

	/**
	 *  Return the primary key for this replica
	 *  @returns	The key
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the primary key for this replica
	 *  @param	primaryKey	The key
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Get the object type id of this replica
	 *  @returns	The type id
	 */
	int GetObjectType() {
		return m_objectType;
	}

	/**
	 *  Set the object type id of this replica
	 *  @param	objectType	The type id
	 */
	void SetObjectType(int objectType) {
		m_objectType = objectType;
	}

	/**
	 *  Get the id representing the current room of this replica
	 *  @returns	The id
	 */
	long long GetRoomId() {
		return m_roomId;
	}

	/**
	 *  Set the id representing the current room of this replica
	 *  @param	roomId	The id
	 */
	void SetRoomId(long long roomId) {
		m_roomId = roomId;
	}

	/**
	 *  Get the uid of the owner of this replica
	 *  @returns	The uid
	 */
	const core::UIDPtr &GetOwnerUid() const {
		return m_ownerUid;
	}

	/**
	 *  Set the uid for the owner of this replica
	 *  @param	ownerUid	The uid
	 */
	void SetOwnerUid(const core::UIDPtr &ownerUid) {
		m_ownerUid = ownerUid;
	}

	/**
	 *  Get the properties of this replica
	 *  @returns	A map of ints (property ids) to objects (property values)
	 */
	std::map<int, net::object::ObjectPtr> &GetProperties() {
		return m_properties;
	}

	/**
	 *  Set the properties of this replica
	 *  @param	properties	A map of ints (property ids) to objects (property values)
	 */
	void SetProperties(const std::map<int, net::object::ObjectPtr> &properties) {
		m_properties = properties;
	}

private:
	long long m_primaryKey;
	int m_objectType;
	long long m_roomId;
	core::UIDPtr m_ownerUid;
	std::map<int, net::object::ObjectPtr> m_properties;
};

typedef std::shared_ptr<Replica> ReplicaPtr;

} } } }
