#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/ParameterMessage.h>
#include <strix/client/core/message/ResponseMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base parameter response class
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix response type - Received from server after request made
 */
class ParameterResponseMessage : public ParameterMessage, public ResponseMessage
{
public:
	STRIX_CLASS(ParameterResponseMessage, ParameterMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.ParameterResponseMessage")
		STRIX_CLASS_SUPER(ResponseMessage)
		STRIX_PROPERTY(m_requestId)
	)

	ParameterResponseMessage() : ParameterMessage(1) {
	}

	/**
	 *  Construct a ParameterResponseMessage that can operate on the given number of classes
	 *  @param	numClasses	The number of MetaClasses
	 */
	ParameterResponseMessage(int numClasses) : ParameterMessage(numClasses) {
	}

	/**
	 *  Construct a ParameterResponseMessage that can operate on the given class
	 *  @param	parameterClass	The MetaClass that can be operated on
	 */
	ParameterResponseMessage(const MetaClass &parameterClass) : ParameterMessage(parameterClass) {
	}

	/**
	 *  Construct a ParameterResponseMessage that can operate on the given classes
	 *  @param	parameterClasses	The MetaClasses that can be operated on
	 */
	ParameterResponseMessage(const std::vector<const MetaClass *> &parameterClasses) : ParameterMessage(parameterClasses) {
	}

	/**
	 *  Get the request ID
	 *  @returns	The request ID
	 */
	int GetRequestId() override {
		return m_requestId;
	}

	/**
	 *  Set request ID
	 *  @param	requestId	The ID
	 */
	void SetRequestId(int requestId) override {
		m_requestId = requestId;
	}

private:
	int m_requestId;
};

} } } }

