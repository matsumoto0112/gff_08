#pragma once

#include <strix/client/core/message/ParameterFailureMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a failed set message 
 *  
 *  A parameter message with parameter classes
 *  
 *  Strix response type - Received from server after request made
 */
class SetFailedResponse : public ParameterFailureMessage
{
public:
	STRIX_CLASS(SetFailedResponse, ParameterFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SetFailedResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	SetFailedResponse() {}

	SetFailedResponse(long long primaryKey) : m_primaryKey(primaryKey) {}
	
	virtual ~SetFailedResponse() {}

	/**
	 *  Get the ID of the object we failed to set on
	 *  @returns	The primary key
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the object ID in this response
	 *  @param	primaryKey	The primary key
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<SetFailedResponse> SetFailedResponsePtr;

} } } }
