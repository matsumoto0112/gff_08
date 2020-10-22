#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/message/ParameterMessage.h>
#include <strix/client/core/message/FailureMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Base parameter class for failure messages
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 */
class ParameterFailureMessage : public ParameterMessage, public FailureMessage
{
public:
	STRIX_CLASS(ParameterFailureMessage, ParameterMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.ParameterFailureMessage")
		STRIX_CLASS_SUPER(FailureMessage)
		STRIX_PROPERTY(m_requestId)
		STRIX_PROPERTY(m_errorCode)
	)

	ParameterFailureMessage() : ParameterMessage(1) {
	}

	/**
	 *  Construct a ParameterFailureMessage that can operate on the given number of classes
	 *  @param	numClasses	The number of MetaClasses
	 */
	ParameterFailureMessage(int numClasses) : ParameterMessage(numClasses) {
	}

	/**
	 *  Construct a ParameterFailureMessage that can operate on the given class
	 *  @param	parameterClass	The MetaClass that can be operated on
	 */
	ParameterFailureMessage(const MetaClass &parameterClass) : ParameterMessage(parameterClass) {
	}

	/**
	 *  Construct a ParameterFailureMessage with an error code, that can operate on a given class
	 *  @param	parameterClass	The MetaClass that can be operated on
	 *  @param	errorCode	The error code of this failure
	 */
	ParameterFailureMessage(const MetaClass &parameterClass, int errorCode) : ParameterMessage(parameterClass), m_errorCode(errorCode) {
	}

	/**
	 *  Construct a ParameterFailureMessage that can operate on the given classes
	 *  @param	parameterClasses	The MetaClasses that can be operated on
	 */
	ParameterFailureMessage(const std::vector<const MetaClass *> &parameterClasses) : ParameterMessage(parameterClasses) {
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

	/**
	 *  Get the failure error code for this message
	 *  @returns	The error code
	 */
	int GetErrorCode() override {
		return m_errorCode;
	}

	/**
	 *  Set the failure error code for this message
	 *  @param	errorCode	The error code
	 */
	void SetErrorCode(int errorCode) override {
		m_errorCode = errorCode;
	}

private:
	int m_requestId;
	int m_errorCode;
};

} } } }
