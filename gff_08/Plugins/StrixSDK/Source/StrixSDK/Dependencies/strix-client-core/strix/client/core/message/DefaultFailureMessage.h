#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/FailureMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  The default failure message
 */
class DefaultFailureMessage : public strix::net::object::Object, public FailureMessage
{
public:
	STRIX_CLASS(DefaultFailureMessage, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DefaultFailureMessage")
		STRIX_CLASS_SUPER(FailureMessage)
		STRIX_PROPERTY(m_requestId)
		STRIX_PROPERTY(m_errorCode)
	)
	
	DefaultFailureMessage() : m_requestId(0), m_errorCode(0) {}

	DefaultFailureMessage(int errorCode) : m_requestId(0), m_errorCode(errorCode) {}

	/**
	 *  Get the request ID
	 *  @returns	The request ID
	 */
	int GetRequestId() override {
	    return m_requestId;
	}

	/**
	 *  Set the request ID
	 *  @param	requestId	The request ID
	 */
	void SetRequestId(int requestId) override {
	    m_requestId = requestId;
	}

	/**
	 *  Get the error code of the failure
	 *  @returns	The error code
	 */
	int GetErrorCode() override {
		return m_errorCode;
	}

	/**
	 *  Set the error code of the failure
	 *  @param	errorCode	The error code
	 */
	void SetErrorCode(int errorCode) override {
		m_errorCode = errorCode;
	}

protected:
	int m_requestId;
	int m_errorCode;
};

} } } }
