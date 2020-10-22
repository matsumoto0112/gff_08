#pragma once

#include <strix/net/object/Object.h>

#include <memory>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base request message class
 *
 *  Strix message type - Requests sent to the server
 */
class RequestMessage
{
public:
	STRIX_BASE_ABSTRACT_CLASS(RequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.RequestMessage")
	)

	/**
	 *  Get the request ID
	 *  @returns	The request ID
	 */
	virtual int GetRequestId() = 0;

	/**
	 *  Set the request ID
	 *  @param	requestId	The request ID
	 */
	virtual void SetRequestId(int requestId) = 0;

protected:
	RequestMessage() {}
};

typedef std::shared_ptr<RequestMessage> RequestMessagePtr;

} } } }
