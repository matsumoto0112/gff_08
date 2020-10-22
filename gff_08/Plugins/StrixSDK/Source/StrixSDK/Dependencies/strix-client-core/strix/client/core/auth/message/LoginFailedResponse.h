#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultFailureMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  Response to a failed login attempt
 *  
 *  Strix response type - Received from server after request made
 */
class LoginFailedResponse : public strix::client::core::message::DefaultFailureMessage
{
public:
	STRIX_CLASS(LoginFailedResponse, DefaultFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.LoginFailedResponse")
	)

	LoginFailedResponse() {}

	LoginFailedResponse(int errorCode) : strix::client::core::message::DefaultFailureMessage(errorCode) {}

	virtual ~LoginFailedResponse() {}

};

typedef std::shared_ptr<LoginFailedResponse> LoginFailedResponsePtr;

} } } } }
