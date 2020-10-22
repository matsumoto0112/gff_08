#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>
#include <strix/client/core/model/manager/filter/Condition.h>

#include <map>
#include <utility>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Request to set several objects by some filter
 *  
 *  Parameter message that operates on its parameter classes
 *  
 *  Strix message type - Requests sent to the server
 */
class SetByMessage : public ParameterRequestMessage
{
public:
	STRIX_CLASS(SetByMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SetByMessage")
		STRIX_PROPERTY(m_filter)
		STRIX_PROPERTY(m_properties)
	)
	
	typedef std::shared_ptr<strix::client::core::model::manager::filter::Condition> ConditionPtr;

	SetByMessage() = default;

	/**
	 *  Construct a SetByMessage with a filter condition and properties to set on objects matching that filter
	 *  @param	condition	The condition to filter by
	 *  @param	initialProperties	The properties to set
	 */
	SetByMessage(ConditionPtr condition, std::map<std::string, strix::net::object::ObjectPtr> initialProperties)
		: m_filter(std::move(condition)), m_properties(std::move(initialProperties)) {}

	/**
	 *  Construct a SetByMessage with a filter condition and properties to set on objects of the parameter class that match the filter
	 *  @param	parameterClass	The type of object to operate on
	 *  @param	condition	The condition to filter by
	 *  @param	initialProperties	The properties to set
	 */
	SetByMessage(const MetaClass &parameterClass, ConditionPtr condition, std::map<std::string, strix::net::object::ObjectPtr> initialProperties)
		: ParameterRequestMessage(parameterClass), m_filter(std::move(condition)), m_properties(std::move(initialProperties)) {}

	virtual ~SetByMessage() = default;

	/**
	 *  Returns the conditional filter for this message
	 *  @returns	The filter
	 */
	const ConditionPtr &GetFilter() const {
		return m_filter;
	}

	/**
	 *  Set the conditional filter in this message
	 *  @param	filter	A condition
	 */
	void SetFilter(const ConditionPtr &filter) {
		m_filter = filter;
	}

	/**
	 *  Get the properties to set
	 *  @returns	The properties
	 */
	const std::map<std::string, strix::net::object::ObjectPtr> &GetProperties() const {
		return m_properties;
	}

	/**
	 *  Set the properties in this message
	 *  @param	properties	The properties
	 */
	void SetProperties(const std::map<std::string, strix::net::object::ObjectPtr> &properties) {
		m_properties = properties;
	}

private:
	ConditionPtr m_filter;
	std::map<std::string, strix::net::object::ObjectPtr> m_properties;
};

typedef std::shared_ptr<SetByMessage> SetByMessagePtr;

} } } }
