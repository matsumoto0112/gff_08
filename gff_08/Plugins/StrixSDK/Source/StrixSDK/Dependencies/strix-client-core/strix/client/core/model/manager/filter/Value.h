#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/model/manager/filter/ValueType.h>
#include <strix/client/core/util/ComparisonUtil.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class Value : public ValueType {
public:
	STRIX_CLASS(Value, ValueType)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.Value")
		STRIX_PROPERTY(m_value)
	)

	Value() {}
	
	Value(strix::net::object::ObjectPtr value) : m_value(std::move(value)) {}
	
	virtual ~Value() {}

	const strix::net::object::ObjectPtr &GetValue() const {
		return m_value;
	}

	void SetValue(const strix::net::object::ObjectPtr &value) {
		m_value = value;
	}

	int Compare(const Object &rhs) const override
	{
		const int base = ValueType::Compare(rhs);
		if (base != 0)
			return base;

		const Value &other = static_cast<const Value &>(rhs);
		
		return util::ComparisonUtil::CompareObjectPtr(m_value, other.m_value);
	}
private:
	strix::net::object::ObjectPtr m_value;
};

} } } } } }
