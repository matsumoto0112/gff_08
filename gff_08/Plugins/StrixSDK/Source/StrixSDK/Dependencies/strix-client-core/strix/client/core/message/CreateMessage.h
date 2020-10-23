#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>

#include <map>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Request to create an object
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix message type - Requests sent to the server
 */
class CreateMessage : public ParameterRequestMessage
{
public:
	STRIX_CLASS(CreateMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.CreateMessage")
		STRIX_PROPERTY(m_properties)
	)

	CreateMessage() {}

	/**
	 *  Construct a CreateMessage to create an object of the type given
	 *  @param	parameterClass	The parameter class
	 */
	CreateMessage(const MetaClass &parameterClass) : ParameterRequestMessage(parameterClass) {}

	/**
	 *  Construct a CreateMessage to create an object with the given properties
	 *  @param	initialProperties	The properties to set
	 */
	CreateMessage(const std::map<std::string, strix::net::object::ObjectPtr> &initialProperties) : m_properties(initialProperties) {}

	/**
	 *  Construct a CreateMessage to create an object of the given type with the given properties
	 *  @param	parameterClass	The parameter class
	 *  @param	initialProperties	The properties to set
	 */
	CreateMessage(const MetaClass &parameterClass, const std::map<std::string, strix::net::object::ObjectPtr> &initialProperties)
		: ParameterRequestMessage(parameterClass), m_properties(initialProperties) {}

	virtual ~CreateMessage() {}

	/**
	 *  Get the properties to set
	 *  @returns	A map of strings (keys) to Objects (values)
	 */
	std::map<std::string, strix::net::object::ObjectPtr> &GetProperties() {
		return m_properties;
	}

	/**
	 *  Set the properties to set
	 *  @param	properties	A map of strings (keys) to Objects (values)
	 */
	void SetProperties(const std::map<std::string, strix::net::object::ObjectPtr> &properties) {
		m_properties = properties;
	}

private:
	std::map<std::string, strix::net::object::ObjectPtr> m_properties;
};

typedef std::shared_ptr<CreateMessage> CreateMessagePtr;

} } } }
