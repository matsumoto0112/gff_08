#pragma once

#include <strix/net/object/Object.h>

#include <memory>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base class for a failure message
 */
class FailureMessage
{
public:
	STRIX_BASE_ABSTRACT_CLASS(FailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.FailureMessage")
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

	/**
	 *  Get the error code
	 *  @returns	The error code
	 */
	virtual int GetErrorCode() = 0;

	/**
	 *  Set the error code
	 *  @param	errorCode	The error code
	 */
	virtual void SetErrorCode(int errorCode) = 0;

protected:
	FailureMessage() {}
};

typedef std::shared_ptr<FailureMessage> FailureMessagePtr;

} } } }
