#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/model/Model.h>

namespace strix { namespace client { namespace room { namespace model {

/**
 *  Represents an abstract model of a room
 */
class Room : public core::model::Model
{
public:
	STRIX_ABSTRACT_CLASS(Room, core::model::Model)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.model.Room")
	)
};

typedef std::shared_ptr<strix::client::room::model::Room> RoomPtr;

} } } }
