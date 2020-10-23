#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/model/Model.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace room { namespace model {

/**
 *  Abstract model of the member of a room
 */
class RoomMember : public core::model::Model
{
public:
	STRIX_ABSTRACT_CLASS(RoomMember, core::model::Model)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.model.RoomMember")
	)
	typedef std::shared_ptr<strix::client::core::UID> UIDPtr;

	/**
	 *  Return the unique identifier of this room member
	 *  @returns	The unique id
	 */
	const virtual UIDPtr &GetUid() const = 0;

	/**
	 *  Set the unique identifier of this room member
	 *  @param	uid	The unique id
	 */
	virtual void SetUid(const UIDPtr &uid) = 0;

	/**
	 *  Return the id of the room this room member belongs to
	 *  @returns	The room id
	 */
	virtual long long GetRoomId() const = 0;

	/**
	 *  Set the room id that this member belongs to
	 *  @param	id	The id to set
	 */
	virtual void SetRoomId(long long id) = 0;
};

typedef std::shared_ptr<strix::client::room::model::RoomMember> RoomMemberPtr;
typedef std::map<strix::client::core::UIDPtr, RoomMemberPtr, net::object::PointerValueComparator> RoomMemberMap;

} } } }
