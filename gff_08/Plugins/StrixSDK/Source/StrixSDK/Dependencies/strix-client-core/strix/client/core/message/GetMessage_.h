#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Request for an object from the server. 
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix message type - Requests sent to the server
 */
class GetMessage_ : public ParameterRequestMessage
{
public:
	STRIX_CLASS(GetMessage_, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.GetMessage")
		STRIX_PROPERTY(m_primaryKey)
	)

	GetMessage_() {}

	/**
	 *  Construct a GetMessage to get an object with the given ID
	 *  @param	primaryKey	The object ID
	 */
	GetMessage_(long long primaryKey) : m_primaryKey(primaryKey) {}

	/**
	 *  Construct a GetMessage to get an object of the given parameter class
	 *  @param	parameterClass	The object type
	 */
	GetMessage_(const MetaClass& parameterClass) : ParameterRequestMessage(parameterClass) {}

	/**
	 *  Construct a GetMessage to get an object of the given parameter class with the given ID
	 *  @param	primaryKey	The object ID
	 */
	GetMessage_(const MetaClass& parameterClass, long long primaryKey)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey) {}
	
	virtual ~GetMessage_() {}

	/**
	 *  Get the object ID in this message
	 *  @returns	The object ID
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the object ID in this message
	 *  @param	primaryKey	The primary key
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<GetMessage_> GetMessagePtr;

} } } }
