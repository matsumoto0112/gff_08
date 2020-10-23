#pragma once

#include <strix/client/room/RoomData.h>
#include <strix/client/match/room/model/MatchRoom.h>
#include <strix/client/match/room/model/MatchRoomMember.h>

namespace strix { namespace client { namespace match {

/**
 *  Class representing the data of a room, extended to provide functionality
 *  facilitating a Match being played
 */
class MatchRoomData : public strix::client::room::RoomData
{
public:
	virtual ~MatchRoomData() {}

	/**
	 *  Return the match room
	 *  @returns	The match room
	 */
	virtual strix::client::match::room::model::MatchRoomPtr GetMatchRoom() const = 0;

	/**
	 *  Set the match room
	 *  @param	pRoom	The match room
	 */
	virtual void SetMatchRoom(const strix::client::match::room::model::MatchRoomPtr &pRoom) = 0;

	/**
	 *  Get this player as a match room member
	 *  @returns	This player
	 */
	virtual strix::client::match::room::model::MatchRoomMemberPtr GetSelfMatchRoomMember() const = 0;

	/**
	 *  Set the current player
	 *  @param	pMember	The current player
	 */
	virtual void SetSelfMatchRoomMember(const strix::client::match::room::model::MatchRoomMemberPtr &pMember) = 0;
};

/**
 *  The default MatchRoomData implementation
 */
class DefaultMatchRoomData : public MatchRoomData
{
public:
	virtual ~DefaultMatchRoomData() {}

	/**
	 *  Get the room of this data
	 *  @returns	The room
	 */
	strix::client::room::model::RoomPtr GetRoom() const override;

	/**
	 *  Set the room of this data
	 *  @param	pRoom	The room
	 */
	void SetRoom(const strix::client::room::model::RoomPtr &pRoom) override;

	/**
	 *  Get this player as a room member
	 *  @returns	This player
	 */
	strix::client::room::model::RoomMemberPtr GetSelfMember() const override;

	/**
	 *  Set the current player
	 *  @param	pMember	The current player
	 */
	void SetSelfMember(const strix::client::room::model::RoomMemberPtr &pMember) override;

	/**
	 *  Get a map of the room members in this room
	 *  @returns	A map of UIDs (member ids) and room members
	 */
	strix::client::room::model::RoomMemberMap &GetRoomMembers() override;

	/**
	 *  Get a map of the room members in this room
	 *  @returns	A map of UIDs (member ids) and room members
	 */
	const strix::client::room::model::RoomMemberMap &GetRoomMembers() const override;

	/**
	 *  Set the room members in this room
	 *  @param	roomMembers	A map of UIDs (member ids) and room members
	 */
	void SetRoomMembers(strix::client::room::model::RoomMemberMap &roomMembers) override;

	/**
	 *  Return the match room
	 *  @returns	The match room
	 */
	strix::client::match::room::model::MatchRoomPtr GetMatchRoom() const override;

	/**
	 *  Set the match room
	 *  @param	pRoom	The match room
	 */
	void SetMatchRoom(const strix::client::match::room::model::MatchRoomPtr &pRoom) override;

	/**
	 *  Get this player as a match room member
	 *  @returns	This player
	 */
	strix::client::match::room::model::MatchRoomMemberPtr GetSelfMatchRoomMember() const override;

	/**
	 *  Set the current player
	 *  @param	pMember	The current player
	 */
	void SetSelfMatchRoomMember(const strix::client::match::room::model::MatchRoomMemberPtr &pMember) override;

private:
	strix::client::room::DefaultRoomData m_roomData;
};

typedef std::shared_ptr<MatchRoomData> MatchRoomDataPtr;

} } }
