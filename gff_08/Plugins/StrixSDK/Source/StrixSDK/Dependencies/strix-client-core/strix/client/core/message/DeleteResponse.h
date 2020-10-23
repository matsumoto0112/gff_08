#pragma once

#include <strix/client/core/message/ParameterResponseMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Response to a successful delete request
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix response type - Received from server after request made
 */
class DeleteResponse : public ParameterResponseMessage
{
public:
	STRIX_CLASS(DeleteResponse, ParameterResponseMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DeleteResponse")
		STRIX_PROPERTY(m_primaryKey)
	)

	DeleteResponse() {}

	DeleteResponse(long long primaryKey) : m_primaryKey(primaryKey) {}
	
	virtual ~DeleteResponse() {}

	/**
	 *  Get the primary key of the deleted object
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

typedef std::shared_ptr<DeleteResponse> DeleteResponsePtr;

} } } }
