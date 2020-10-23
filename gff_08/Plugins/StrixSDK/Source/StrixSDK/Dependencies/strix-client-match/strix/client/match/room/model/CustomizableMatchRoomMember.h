#pragma once

#include <strix/client/match/room/model/MatchRoomMember.h>

namespace strix { namespace client { namespace match { namespace room { namespace model {

/**
 *  An implementation of MatchRoomMember with customizable properties
 */
class CustomizableMatchRoomMember : public MatchRoomMember
{
public:
	STRIX_CLASS(CustomizableMatchRoomMember, MatchRoomMember)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.match.room.model.CustomizableMatchRoomMember")
		STRIX_PROPERTY(m_properties)
	)
	
	CustomizableMatchRoomMember() {}
	
	virtual ~CustomizableMatchRoomMember() {}

	/**
	 *  Get this members customizable properties
	 *  @returns	A map of strings (property names) and objects (values)
	 */
	std::map<std::string, strix::net::object::ObjectPtr> &GetProperties() {
		return m_properties;
	}

	/**
	 *  Set this members customizable properties
	 *  @param	properties	A map of strings (property names) and objects (values)
	 */
	void SetProperties(std::map<std::string, strix::net::object::ObjectPtr> properties) {
		m_properties = std::move(properties);
	}

private:
	std::map<std::string, strix::net::object::ObjectPtr> m_properties;
};

typedef std::shared_ptr<CustomizableMatchRoomMember> CustomizableMatchRoomMemberPtr;

} } } } }
