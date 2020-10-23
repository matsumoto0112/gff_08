#pragma once

#include <strix/client/core/message/ParameterFailureMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a failed delete request
 * 
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix response type - Received from server after request made
 */
class DeleteFailedResponse : public ParameterFailureMessage
{
public:
	STRIX_CLASS(DeleteFailedResponse, ParameterFailureMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DeleteFailedResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	DeleteFailedResponse() {}

	DeleteFailedResponse(long long primaryKey) : m_primaryKey(primaryKey) {}
	
	virtual ~DeleteFailedResponse() {}

	/**
	 *  Get the primary key of the object that failed to delete
	 *  @returns	The primary key
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the object primary key in this response
	 *  @param	primaryKey	The primary key
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

} } } }
