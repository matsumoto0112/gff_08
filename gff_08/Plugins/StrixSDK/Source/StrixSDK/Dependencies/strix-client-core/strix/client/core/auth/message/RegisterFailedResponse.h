#pragma once

#include <strix/client/core/UID.h>
#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultFailureMessage.h>

namespace strix { namespace client { namespace core { namespace auth { namespace message {

/**
 *  Response to a failed register request
 *  
 *  Strix response type - Received from server after request made
 */
class RegisterFailedResponse : public strix::client::core::message::DefaultFailureMessage
{
public:
	STRIX_CLASS(RegisterFailedResponse, DefaultFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.auth.message.RegisterFailedResponse")
	)

	RegisterFailedResponse() {}

	RegisterFailedResponse(int errorCode) : strix::client::core::message::DefaultFailureMessage(errorCode) {}

	virtual ~RegisterFailedResponse() {}

};

typedef std::shared_ptr<RegisterFailedResponse> RegisterFailedResponsePtr;

} } } } }
