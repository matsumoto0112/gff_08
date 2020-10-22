#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/message/DefaultResponseMessage.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response to a successful direct relay
 *  
 *  Strix response type - Received from server after request made
 */
class RoomDirectRelayResponse : public strix::client::core::message::DefaultResponseMessage
{
public:
	STRIX_CLASS(RoomDirectRelayResponse, DefaultResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomDirectRelayResponse")
	)

	RoomDirectRelayResponse() {}
		
	virtual ~RoomDirectRelayResponse() {}
};

typedef std::shared_ptr<RoomDirectRelayResponse> RoomDirectRelayResponsePtr;

} } } }
