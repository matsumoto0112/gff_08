#pragma once

#include <strix/client/core/model/manager/filter/OrderType.h>
#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class Order : public strix::net::object::Object {
public:
	STRIX_CLASS(Order, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.Order")
		STRIX_PROPERTY(m_fieldName)
		STRIX_PROPERTY_TYPED(m_orderType, int)
	)

	Order() {}
	
	Order(const std::string &fieldName, OrderType orderType) {
		m_fieldName = fieldName;
		m_orderType = orderType;
	}
	
	virtual ~Order() {}

	std::string &GetFieldName() {
		return m_fieldName;
	}

	void SetFieldName(const std::string &fieldName) {
		m_fieldName = fieldName;
	}
	
	OrderType GetOrderType() {
		return m_orderType;
	}
	
	void SetOrderType(const OrderType orderType) {
		m_orderType = orderType;
	}

	int Compare(const Object &rhs) const override
	{
		const net::object::MetaClass &metaClass = GetMetaClass();
		const net::object::MetaClass &metaClass2 = rhs.GetMetaClass();
	
		if (&metaClass > &metaClass2)
			return 1;
		if (&metaClass < &metaClass2)
			return -1;

		const Order & other = static_cast<const Order &>(rhs);

		if (m_fieldName > other.m_fieldName)
			return 1;
		if (m_fieldName < other.m_fieldName)
			return -1;
		
		if (m_orderType > other.m_orderType)
			return 1;
		if (m_orderType < other.m_orderType)
			return -1;

		return 0;
	}

private:
	std::string m_fieldName;
	OrderType m_orderType;
};

typedef std::shared_ptr<strix::client::core::model::manager::filter::Order> OrderPtr;

} } } } } }
