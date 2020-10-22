#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/ResponseMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  The default response message
 *  
 *  Strix response type - Received from server after request made
 */
class DefaultResponseMessage : public strix::net::object::Object, public ResponseMessage
{
public:
	STRIX_CLASS(DefaultResponseMessage, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DefaultResponseMessage")
		STRIX_CLASS_SUPER(ResponseMessage)
		STRIX_PROPERTY(m_requestId)
	)

	DefaultResponseMessage() : m_requestId(0) {}

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

protected:
	int m_requestId;
};

} } } }
