#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/client/core/model/manager/filter/Field.h>
#include <strix/client/core/model/manager/filter/ValueType.h>
#include <strix/client/core/util/ComparisonUtil.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class NotEquals : public Condition {
public:
	STRIX_CLASS(NotEquals, Condition)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.NotEquals")
		STRIX_PROPERTY(m_left)
		STRIX_PROPERTY(m_right)
	)

	typedef std::shared_ptr<Field> FieldPtr;
	typedef std::shared_ptr<ValueType> ValueTypePtr;

	NotEquals() {}

	NotEquals(FieldPtr left, ValueTypePtr right) : m_left(std::move(left)), m_right(std::move(right)) {}

	virtual ~NotEquals() {}

	const FieldPtr &GetLeft() const {
		return m_left;
	}

	void SetLeft(const FieldPtr &left) {
		m_left = left;
	}
	
	const ValueTypePtr &GetRight() const {
		return m_right;
	}
	
	void SetRight(const ValueTypePtr &right) {
		m_right = right;
	}

	int Compare(const Object &rhs) const override
	{
		const int base = Condition::Compare(rhs);
		if (base != 0)
			return base;

		const NotEquals & other = static_cast<const NotEquals &>(rhs);
		
		const int leftComp = util::ComparisonUtil::CompareObjectPtr(m_left, other.m_left);
		if (leftComp != 0)
			return leftComp;
		
		return util::ComparisonUtil::CompareObjectPtr(m_right, other.m_right);
	}

private:
	FieldPtr m_left;
	ValueTypePtr m_right;
};

} } } } } }
