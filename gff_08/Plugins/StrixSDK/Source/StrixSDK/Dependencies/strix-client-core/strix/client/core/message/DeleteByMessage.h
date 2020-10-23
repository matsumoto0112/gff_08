#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/net/object/WrapperObject.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Request to delete all objects matching a condition
 *  
 *  Parameter classes can take a number of MetaClasses representing the Objects they can operate on
 *  
 *  Strix message type - Requests sent to the server
 */
class DeleteByMessage : public ParameterRequestMessage
{
public:
	STRIX_CLASS(DeleteByMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.DeleteByMessage")
		STRIX_PROPERTY(m_condition)
	)
	
	typedef std::shared_ptr<strix::client::core::model::manager::filter::Condition> ConditionPtr;

	DeleteByMessage() {}

	/**
	 *  Construct a DeleteByMessage with the given condition to match against
	 *  @param	condition	The condition
	 */
	DeleteByMessage(const ConditionPtr &condition) : m_condition(condition) {}

	/**
	 *  Construct a DeleteByMessage to delete objects of the given class
	 *  @param	parameterClass	The parameter class
	 */
	DeleteByMessage(const MetaClass &parameterClass) : ParameterRequestMessage(parameterClass) {}

	/**
	 *  Construct a DeleteByMessage to delete objects of the given class matching some condition
	 *  @param	parameterClass	The parameter class
	 *  @param	condition	The condition
	 */
	DeleteByMessage(const MetaClass &parameterClass, const ConditionPtr &condition)
		: ParameterRequestMessage(parameterClass), m_condition(condition) {}
	
	virtual ~DeleteByMessage() {}

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

typedef std::shared_ptr<DeleteByMessage> DeleteByMessagePtr;

} } } }
