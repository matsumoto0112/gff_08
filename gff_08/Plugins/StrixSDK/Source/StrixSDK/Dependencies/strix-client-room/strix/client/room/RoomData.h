#pragma once

#include <strix/client/room/model/Room.h>
#include <strix/client/room/model/RoomMember.h>

#include <memory>

namespace strix { namespace client { namespace room {

/**
 *  Information about a room
 */
class RoomData
{
public:
	virtual ~RoomData() {}

	/**
	 *  Return the room that this RoomData belongs to
	 *  @returns	The room
	 */
	virtual strix::client::room::model::RoomPtr GetRoom() const = 0;

	/**
	 *  Set the room that this RoomData belongs to
	 *  @param	pRoom	The room to set
	 */
	virtual void SetRoom(const strix::client::room::model::RoomPtr &pRoom) = 0;

	/**
	 *  Get the member of this room representing the current player
	 *  @returns	The member
	 */
	virtual strix::client::room::model::RoomMemberPtr GetSelfMember() const = 0;

	/*
	 *  Set the member of this room representing the current player
	 *  @param	pMember	The member to set
	 */
	virtual void SetSelfMember(const strix::client::room::model::RoomMemberPtr &pMember) = 0;

	/**
	 *  Get all members in this room
	 *  @returns	A map of UIDs to RoomMemberPtr's representing the members of this room
	 */
	virtual strix::client::room::model::RoomMemberMap &GetRoomMembers() = 0;

	/**
	 *  Get all members in this room
	 *  @returns	A map of UIDs to RoomMemberPtr's representing the members of this room
	 */
	virtual const strix::client::room::model::RoomMemberMap &GetRoomMembers() const = 0;

	/**
	 *  Set all members in this room
	 *  @param	roomMembers	A map of UIDs to RoomMemberPtr's representing the members to set
	 */
	virtual void SetRoomMembers(strix::client::room::model::RoomMemberMap &roomMembers) = 0;
};

typedef std::shared_ptr<RoomData> RoomDataPtr;

/**
 *  Default RoomData implementation
 */
class DefaultRoomData : public RoomData
{
public:

	/**
	 *  Return the room that this RoomData belongs to
	 *  @returns	The room
	 */
	strix::client::room::model::RoomPtr GetRoom() const override;

	/**
	 *  Set the room that this RoomData belongs to
	 *  @param	pRoom	The room to set
	 */
	void SetRoom(const strix::client::room::model::RoomPtr &pRoom) override;

	/**
	 *  Get the member of this room representing the current player
	 *  @returns	The member
	 */
	strix::client::room::model::RoomMemberPtr GetSelfMember() const override;

	/*
	 *  Set the member of this room representing the current player
	 *  @param	pMember	The member to set
	 */
	void SetSelfMember(const strix::client::room::model::RoomMemberPtr &pMember) override;

	/**
	 *  Get all members in this room
	 *  @returns	A map of UIDs to RoomMemberPtr's representing the members of this room
	 */
	strix::client::room::model::RoomMemberMap &GetRoomMembers() override;

	/**
	 *  Get all members in this room
	 *  @returns	A map of UIDs to RoomMemberPtr's representing the members of this room
	 */
	const strix::client::room::model::RoomMemberMap &GetRoomMembers() const override;

	/**
	 *  Set all members in this room
	 *  @param   roomMembers A map of UIDs to RoomMemberPtr's representing the members to set
	 */
	void SetRoomMembers(strix::client::room::model::RoomMemberMap &roomMembers) override;

private:
	strix::client::room::model::RoomPtr m_pRoom;
	strix::client::room::model::RoomMemberPtr m_pSelfMember;
	strix::client::room::model::RoomMemberMap m_roomMembers;
};

} } }
