#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/message/DefaultResponseMessage.h>

namespace strix { namespace client { namespace room { namespace message {

/**
 *  A response to a successful room relay
 *  
 *  Strix response type - Received from server after request made
 */
class RoomRelayResponse : public strix::client::core::message::DefaultResponseMessage
{
public:
	STRIX_CLASS(RoomRelayResponse, DefaultResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomRelayResponse")
	)

	RoomRelayResponse() {}
		
	virtual ~RoomRelayResponse() {}
};

typedef std::shared_ptr<RoomRelayResponse> RoomRelayResponsePtr;

} } } }
