#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultFailureMessage.h>

namespace strix { namespace client { namespace core { namespace session { namespace message {

/**
 *  A response to a failed restore session request
 *  
 *  Strix response type - Received from server after request made
 */
class RestoreSessionFailedResponse : public strix::client::core::message::DefaultFailureMessage
{
public:
	STRIX_CLASS(RestoreSessionFailedResponse, DefaultFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.RestoreSessionFailedResponse")
	)

	RestoreSessionFailedResponse() {}

	RestoreSessionFailedResponse(int errorCode) : strix::client::core::message::DefaultFailureMessage(errorCode) {}

	virtual ~RestoreSessionFailedResponse() {}

};

} } } } }
