#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultFailureMessage.h>

namespace strix { namespace client { namespace core { namespace session { namespace message {

/**
 *  Response to a failed session challenge request
 *  
 *  Strix response type - Received from server after request made
 */
class SessionChallengeFailedResponse : public strix::client::core::message::DefaultFailureMessage
{
public:
	STRIX_CLASS(SessionChallengeFailedResponse, DefaultFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.SessionChallengeFailedResponse")
	)

	SessionChallengeFailedResponse() {}

	SessionChallengeFailedResponse(int errorCode) : strix::client::core::message::DefaultFailureMessage(errorCode) {}

	virtual ~SessionChallengeFailedResponse() {}

};

} } } } }
