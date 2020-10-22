#pragma once

#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>
#include <strix/client/core/message/DefaultFailureMessage.h>

namespace strix { namespace client { namespace room { namespace message {
	
/**
 *  A response to a failed room relay request
 *  
 *  Strix response type - Received from server after request made
 */
class RoomRelayFailureResponse : public strix::client::core::message::DefaultFailureMessage
{
public:
	STRIX_CLASS(RoomRelayFailureResponse, DefaultFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.room.message.RoomRelayFailureResponse")
	)

	RoomRelayFailureResponse() {}
		
	virtual ~RoomRelayFailureResponse() {}
};

typedef std::shared_ptr<RoomRelayFailureResponse> RoomRelayFailureResponsePtr;

} } } }
