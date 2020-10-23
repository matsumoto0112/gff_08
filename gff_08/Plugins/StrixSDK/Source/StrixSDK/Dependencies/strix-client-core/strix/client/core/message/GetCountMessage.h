#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Request for a count of models matching a certain condition
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix message type - Requests sent to the server
 */
class GetCountMessage : public ParameterRequestMessage
{
public:
	STRIX_CLASS(GetCountMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.GetCountMessage")
		STRIX_PROPERTY(m_condition)
	)

	typedef std::shared_ptr<strix::client::core::model::manager::filter::Condition> ConditionPtr;

	GetCountMessage() {}

	/**
	 *  Construct a GetCountMessage to get from a given parameter class
	 *  @param	parameterClass	The parameter class
	 */
	GetCountMessage(const MetaClass &parameterClass) : ParameterRequestMessage(parameterClass) {}

	/**
	 *  Construct a GetCountMessage to get from a given parameter class and the count of models matching a condition
	 *  @param	parameterClass	The parameter class
	 *  @param	condition	The condition to match against
	 */
	GetCountMessage(const MetaClass &parameterClass, const ConditionPtr &condition) : ParameterRequestMessage(parameterClass), m_condition(condition) {}

	virtual ~GetCountMessage() {}

	/**
	 *  Get the condition to match against
	 *  @returns	The condition
	 */
	const ConditionPtr &GetCondition() const {
		return m_condition;
	}

	/**
	 *  Set the condition to match against
	 *  @param	condition	The condition 
	 */
	void SetCondition(const ConditionPtr &condition) {
		m_condition = condition;
	}

private:
	ConditionPtr m_condition;
};

typedef std::shared_ptr<GetCountMessage> GetCountMessagePtr;

} } } }
