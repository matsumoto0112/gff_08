#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/DefaultFailureMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Failure message for signalling failure locally. Used when a failure message 
 *  is needed but the server cannot send one (e.g, on a connection timeout)
 */
class LocalFailureMessage : public DefaultFailureMessage
{
public:
	STRIX_CLASS(LocalFailureMessage, DefaultFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.LocalFailureMessage")
	)

  LocalFailureMessage() {}

	LocalFailureMessage(int errorCode) : DefaultFailureMessage(errorCode) {}

	virtual ~LocalFailureMessage() {}

};

} } } }
