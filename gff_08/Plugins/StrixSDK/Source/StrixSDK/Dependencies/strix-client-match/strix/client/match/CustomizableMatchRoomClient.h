#pragma once

#include <strix/client/match/MatchRoomClient.h>
#include <strix/client/match/room/model/CustomizableMatchRoom.h>
#include <strix/client/match/room/model/CustomizableMatchRoomMember.h>

namespace strix { namespace client { namespace match {

/**
 *  An implementation of a MatchRoomClient that uses the CustomizableMatchNode and CustomizableMatchNodeRoom as the models
 */
class CustomizableMatchRoomClient : public MatchRoomClient
{
public:
	CustomizableMatchRoomClient() : MatchRoomClient(room::model::CustomizableMatchRoom::s_GetMetaClass(),
	                                                room::model::CustomizableMatchRoomMember::s_GetMetaClass())
	{
	}

	virtual ~CustomizableMatchRoomClient() = default;

	void OnSetResponse(core::request::RequestResult<core::message::SetResponsePtr> result) override;

	void OnRoomSetMemberResponse(core::request::RequestResult<client::room::message::RoomSetMemberResponsePtr> result) override;

private:
	void AddPropertiesToMap(std::map<std::string, strix::net::object::ObjectPtr> &source, std::map<std::string, strix::net::object::ObjectPtr> *destination);

	static const std::string PropertiesFieldName;
};

typedef std::shared_ptr<CustomizableMatchRoomClient> CustomizableMatchRoomClientPtr;

}}}
