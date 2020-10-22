#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>

#include <map>
#include <utility>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  A request to set properties on a model
 *  
 *  A parameter request that can operate on its parameter classes
 *  
 *  Strix message type - Requests sent to the server
 */
class SetMessage : public ParameterRequestMessage
{
public:
	STRIX_CLASS(SetMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SetMessage")
		STRIX_PROPERTY(m_primaryKey)
		STRIX_PROPERTY(m_properties)
	)

	SetMessage() {}

	/**
	 *  Construct a SetMessage that will operate on a given class
	 *  @param	parameterClass	The type of the object this message will set properties on
	 */
	SetMessage(const MetaClass &parameterClass) : ParameterRequestMessage(parameterClass) {}

	/**
	 *  Construct a SetMessage for an object with the primary key, setting initial properties
	 *  @param	primaryKey	The ID of the object to set properties on
	 *  @param	initialProperties	The properties to set
	 */
	SetMessage(long long primaryKey, std::map<std::string, strix::net::object::ObjectPtr> initialProperties)
		: m_primaryKey(primaryKey), m_properties(std::move(initialProperties)) {}

	/**
	 *  Construct a SetMessage for an object of the given type with the primary key, setting initial properties
	 *  @param	parameterClass	The type of the object this message will set properties on
	 *  @param	primaryKey	The ID of the object to set properties on
	 *  @param	initialProperties	The properties to set
	 */
	SetMessage(const MetaClass &parameterClass, long long primaryKey, std::map<std::string, strix::net::object::ObjectPtr> initialProperties)
		: ParameterRequestMessage(parameterClass), m_primaryKey(primaryKey), m_properties(std::move(initialProperties)) {}

	virtual ~SetMessage() {}

	/**
	 *  Get the ID of the object this request is for
	 *  @returns	The primary key
	 */
	long long GetPrimaryKey() {
		return m_primaryKey;
	}

	/**
	 *  Set the object ID this request is for
	 *  @param	primaryKey	The primary key
	 */
	void SetPrimaryKey(long long primaryKey) {
		m_primaryKey = primaryKey;
	}

	/**
	 *  Get the properties to be set
	 *  @returns	A map of strings (keys) to Objects (values)
	 */
	std::map<std::string, strix::net::object::ObjectPtr> &GetProperties() {
		return m_properties;
	}

	/**
	 *  Set the properties to be set
	 *  @param	properties	A map of strings (keys) to Objects (values)
	 */
	void SetProperties(std::map<std::string, strix::net::object::ObjectPtr> properties) {
		m_properties = std::move(properties);
	}

private:
	long long m_primaryKey;
	std::map<std::string, strix::net::object::ObjectPtr> m_properties;
};

typedef std::shared_ptr<SetMessage> SetMessagePtr;

} } } }
