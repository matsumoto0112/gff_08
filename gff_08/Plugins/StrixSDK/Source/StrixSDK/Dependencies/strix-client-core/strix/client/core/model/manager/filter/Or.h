#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/client/core/util/ComparisonUtil.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class Or : public Condition {
public:
	STRIX_CLASS(Or, Condition)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.Or")
		STRIX_PROPERTY(m_conditions)
	)

	typedef std::vector<ConditionPtr> ConditionVector;

	Or() {}

	Or(ConditionVector conditions) : m_conditions(std::move(conditions)) {}

	virtual ~Or() {}

	ConditionVector &GetConditions() {
		return m_conditions;
	}

	void SetConditions(ConditionVector &conditions) {
		m_conditions = conditions;
	}

	int Compare(const Object &rhs) const override
	{
		const int base = Condition::Compare(rhs);
		if (base != 0)
			return base;

		const Or & other = static_cast<const Or &>(rhs);
		return util::ComparisonUtil::CompareObjectPtrList(m_conditions, other.m_conditions);
	}

private:
	ConditionVector m_conditions;
};

} } } } } }
