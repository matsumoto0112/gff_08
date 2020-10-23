#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/RequestMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  The default request message
 *  
 *  Strix message type - Requests sent to the server
 */
class DefaultRequestMessage : public strix::net::object::Object, public RequestMessage
{
public:
	STRIX_ABSTRACT_CLASS(DefaultRequestMessage, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DefaultRequestMessage")
		STRIX_CLASS_SUPER(RequestMessage)
		STRIX_PROPERTY(m_requestId)
	)
	
	DefaultRequestMessage() : m_requestId(0) {}

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
