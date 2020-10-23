#pragma once

#include <strix/client/core/message/ParameterRequestMessage.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/client/core/model/manager/filter/Order.h>

namespace strix { namespace client { namespace core { namespace message {

/**
 *  Request for a list of objects from the server matching some condition
 *  
 *  Parameter request that operates on objects of its parameter type
 *  
 *  Strix message type - Requests sent to the server
 */
class SearchMessage : public ParameterRequestMessage
{
public:
	STRIX_CLASS(SearchMessage, ParameterRequestMessage)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.message.SearchMessage")
		STRIX_PROPERTY(m_limit)
		STRIX_PROPERTY(m_offset)
		STRIX_PROPERTY(m_condition)
		STRIX_PROPERTY(m_order)
	)

	SearchMessage() : m_limit(0), m_offset(0) {}

	/**
	 *  Construct a SearchMessage with the given search parameters
	 *  @param	limit	The max number of objects to return from the search
	 *  @param	offset	The offset into the search list. offset:20 and limit:20 will find objects 20 through to 40 of the matched list
	 *  @param	condition	The search condition to match against
	 */
	SearchMessage(int limit, int offset, const model::manager::filter::ConditionPtr &condition)
		: m_limit(limit),
		  m_offset(offset),
		  m_condition(condition) {}

	/**
	 *  Construct a SearchMessage with the given search parameters
	 *  @param	limit	The max number of objects to return from the search
	 *  @param	offset	The offset into the search list. offset:20 and limit:20 will find objects 20 through to 40 of the matched list
	 *  @param	condition	The search condition to match against
	 *  @param	order	The order in which to return results
	 */
	SearchMessage(int limit, int offset, const model::manager::filter::ConditionPtr &condition, const model::manager::filter::OrderPtr &order)
		: m_limit(limit),
		  m_offset(offset),
		  m_condition(condition),
		  m_order(order) {}

	/**
	 *  Construct a SearchMessage that will search for objects of the given parameter type
	 *  @param	parameterClass	The type of object to search for
	 */
	SearchMessage(const MetaClass &parameterClass) : ParameterRequestMessage(parameterClass), m_limit(0), m_offset(0) {}

	/**
	 *  Construct a SearchMessage with the given search parameters for the given object type
	 *  @param	parameterClass	The type of object to search for
	 *  @param	limit	The max number of objects to return from the search
	 *  @param	offset	The offset into the search list. offset:20 and limit:20 will find objects 20 through to 40 of the matched list
	 *  @param	condition	The search condition to match against
	 */
	SearchMessage(const MetaClass &parameterClass, int limit, int offset, const model::manager::filter::ConditionPtr &condition)
		: ParameterRequestMessage(parameterClass),
		  m_limit(limit),
		  m_offset(offset),
		  m_condition(condition) {}

	/**
	 *  Construct a SearchMessage with the given search parameters for the given object type
	 *  @param	parameterClass	The type of object to search for
	 *  @param	limit	The max number of objects to return from the search
	 *  @param	offset	The offset into the search list. offset:20 and limit:20 will find objects 20 through to 40 of the matched list
	 *  @param	condition	The search condition to match against
	 *  @param	order	The order in which to return results
	 */
	SearchMessage(const MetaClass &parameterClass, int limit, int offset, const model::manager::filter::ConditionPtr &condition, const model::manager::filter::OrderPtr &order)
		: ParameterRequestMessage(parameterClass),
		  m_limit(limit),
		  m_offset(offset),
		  m_condition(condition),
		  m_order(order) {}

	virtual ~SearchMessage() {}

	/**
	 *  Get the max number of items to return
	 *  @returns	The search limit
	 */
	int GetLimit() {
		return m_limit;
	}

	/**
	 *  Set the max number of items to return
	 *  @param	limit	The search limit
	 */
	void SetLimit(int limit) {
		m_limit = limit;
	}

	/**
	 *  Get the offset into the list of results to start returning
	 *  @returns	The offset
	 */
	int GetOffset() {
		return m_offset;
	}

	/**
	 *  Set the offset into the list of results to start returning
	 *  @param	offset	The offset
	 */
	void SetOffset(int offset) {
		m_offset = offset;
	}

	/**
	 *  Get the condition to search with
	 *  @returns	The condition
	 */
	const model::manager::filter::ConditionPtr &GetCondition() const {
		return m_condition;
	}

	/**
	 *  Set the condition to search with
	 *  @param	condition	The condition
	 */
	void SetCondition(const model::manager::filter::ConditionPtr &condition) {
		m_condition = condition;
	}

	/**
	 *  Get the order to return results in
	 *  @returns	The order
	 */
	const model::manager::filter::OrderPtr &GetOrder() const {
		return m_order;
	}

	/**
	 *  Set the order to return results in
	 *  @param	order	The order
	 */
	void SetOrder(const model::manager::filter::OrderPtr &order) {
		m_order = order;
	}

private:
	int m_limit;
	int m_offset;
	model::manager::filter::ConditionPtr m_condition;
	model::manager::filter::OrderPtr m_order;
};

typedef std::shared_ptr<SearchMessage> SearchMessagePtr;

} } } }
