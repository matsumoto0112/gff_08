#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/client/core/model/manager/filter/Field.h>
#include <strix/client/core/util/ComparisonUtil.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class IsNull : public Condition {
public:
	STRIX_CLASS(IsNull, Condition)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.IsNull")
		STRIX_PROPERTY(m_field)
	)

	typedef std::shared_ptr<Field> FieldPtr;

	IsNull() {}

	IsNull(const FieldPtr &field) : m_field(field) {}

	virtual ~IsNull() {}

	const FieldPtr &GetField() const {
		return m_field;
	}

	void SetField(const FieldPtr &field) {
		m_field = field;
	}

	int Compare(const Object &rhs) const override
	{
		const int base = Condition::Compare(rhs);
		if (base != 0)
			return base;

		const IsNull & other = static_cast<const IsNull &>(rhs);

		return util::ComparisonUtil::CompareObjectPtr(m_field, other.m_field);
	}

private:
	FieldPtr m_field;
};

} } } } } }
