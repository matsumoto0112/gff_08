#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Request for an object to be deleted
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix message type - Requests sent to the server
 */
class DeleteMessage : public ParameterRequestMessage
{
public:
	STRIX_CLASS(DeleteMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DeleteMessage")
		STRIX_PROPERTY(m_primaryKey)
	)

	DeleteMessage() {}

	/**
	 *  Construct a DeleteMessage to delete the object with the given primary key
	 *  @param	primaryKey	The object's primary key
	 */
	DeleteMessage(long long primaryKey) : m_primaryKey(primaryKey) {}

	/**
	 *  Construct a DeleteMessage to delete an object of the given parameter class
	 *  @param	parameterClass	The type of Object
	 */
	DeleteMessage(const MetaClass &parameterClass) : ParameterRequestMessage(parameterClass) {}

	/**
	 *  Construct a DeleteMessage to delete an object of the given type with the given primary key
	 *  @param	parameterClass	The type of Object
	 *  @param	primaryKey	The object's primary key
	 */
	DeleteMessage(const MetaClass &parameterClass, long long primaryKey)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey) {}

	virtual ~DeleteMessage() {}

	/**
	 *  Get the primary key of the object to delete
	 *  @returns	The primary key
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the primary key of the object to delete
	 *  @param	primaryKey	The primary key
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

private:
	long long m_primaryKey;
};

typedef std::shared_ptr<DeleteMessage> DeleteMessagePtr;

} } } }
