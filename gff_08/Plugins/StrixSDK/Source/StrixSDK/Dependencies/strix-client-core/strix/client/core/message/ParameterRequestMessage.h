#pragma once

#include <strix/client/core/message/ParameterMessage.h>
#include <strix/client/core/message/RequestMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base parameter request class
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix message type - Requests sent to the server
 */
class ParameterRequestMessage : public ParameterMessage, public RequestMessage
{
public:
	STRIX_CLASS(ParameterRequestMessage, ParameterMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.ParameterRequestMessage")
		STRIX_CLASS_SUPER(RequestMessage)
		STRIX_PROPERTY(m_requestId)
	)

	ParameterRequestMessage() : ParameterMessage(1) {
	}

	/**
	 *  Construct a ParameterRequestMessage that can operate on the given number of classes
	 *  @param	numClasses	The number of MetaClasses
	 */
	ParameterRequestMessage(int numClasses) : ParameterMessage(numClasses) {
	}

	/**
	 *  Construct a ParameterRequestMessage that can operate on the given class
	 *  @param	parameterClass	The MetaClass that can be operated on
	 */
	ParameterRequestMessage(const MetaClass &parameterClass) : ParameterMessage(parameterClass) {
	}

	/**
	 *  Construct a ParameterRequestMessage that can operate on the given classes
	 *  @param	parameterClasses	The MetaClasses that can be operated on
	 */
	ParameterRequestMessage(const std::vector<const MetaClass *> &parameterClasses) : ParameterMessage(parameterClasses) {
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

