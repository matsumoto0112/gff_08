#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/Object.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a successful set properties message
 *  
 *  Parameter message with parameter classes
 *  
 *  Strix response type - Received from server after request made
 */
class SetResponse : public ParameterResponseMessage
{
public:
	STRIX_CLASS(SetResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SetResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	SetResponse() {}
	
	SetResponse(long long primaryKey) : m_primaryKey(primaryKey) {}
	
	virtual ~SetResponse() {}

	/**
	 *  Get the ID for the object that was set
	 *  @returns	The primary key
	 */
	long long GetPrimaryKey() const {
		return m_primaryKey;
	}

	/**
	 *  Set the object ID in this response
	 *  @param	primaryKey	The primary key
	 */
	void SetPrimaryKey(const long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<SetResponse> SetResponsePtr;

} } } }
