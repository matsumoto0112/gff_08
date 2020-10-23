#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultRequestMessage.h>

namespace strix { namespace client { namespace core { namespace session { namespace message {

/**
 *  Request to perform authentication for a session
 *  
 *  Strix message type - Requests sent to the server
 */
class SessionChallengeMessage : public strix::client::core::message::DefaultRequestMessage
{
public:
	STRIX_CLASS(SessionChallengeMessage, DefaultRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.SessionChallengeMessage")
	)

	SessionChallengeMessage() {}

	virtual ~SessionChallengeMessage() {}

};

typedef std::shared_ptr<SessionChallengeMessage> SessionChallengeMessagePtr;

} } } } }
