#pragma once

#include <strix/client/core/message/CreateMessage.h>

#include <map>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  Message for creating a room with no initial owner
 *  
 *  Strix message type - Used for sending requests to the server  
 */
class OwnerlessRoomCreateMessage : public strix::client::core::message::CreateMessage
{
public:
	STRIX_CLASS(OwnerlessRoomCreateMessage, CreateMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.OwnerlessRoomCreateMessage")
	)

	OwnerlessRoomCreateMessage() {}

	OwnerlessRoomCreateMessage(const MetaClass &parameterClass)
		: CreateMessage(parameterClass) {}

	OwnerlessRoomCreateMessage(const std::map<std::string, strix::net::object::ObjectPtr> &initialProperties)
		: CreateMessage(initialProperties) {}

	OwnerlessRoomCreateMessage(const MetaClass &parameterClass, const std::map<std::string, strix::net::object::ObjectPtr> &initialProperties)
		: CreateMessage(parameterClass, initialProperties) {}

	virtual ~OwnerlessRoomCreateMessage() {}

};

typedef std::shared_ptr<OwnerlessRoomCreateMessage> OwnerlessRoomCreateMessagePtr;

} } } }
