#pragma once

#include <strix/net/object/Object.h>

#include <memory>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base response message class
 *  
 *  Strix response type - Received from server after request made
 */
class ResponseMessage
{
public:
	STRIX_BASE_ABSTRACT_CLASS(ResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.ResponseMessage")
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
	ResponseMessage() {}
};

typedef std::shared_ptr<ResponseMessage> ResponseMessagePtr;

} } } }
