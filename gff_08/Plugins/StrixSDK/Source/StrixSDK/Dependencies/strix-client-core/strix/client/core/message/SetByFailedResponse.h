#pragma once

#include <strix/client/core/message/ParameterFailureMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a failed set by request
 *  
 *  Parameter message that uses parameter classes
 *  
 *  Strix message type - This message is sent by the server to clients
 */
class SetByFailedResponse : public ParameterFailureMessage
{
public:
	STRIX_CLASS(SetByFailedResponse, ParameterFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SetByFailedResponse")
	)

	SetByFailedResponse() {}
	
	virtual ~SetByFailedResponse() {}
};

typedef std::shared_ptr<SetByFailedResponse> SetByFailedResponsePtr;

} } } }
