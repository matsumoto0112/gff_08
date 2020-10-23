#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/model/manager/filter/Condition.h>
#include <strix/client/core/model/manager/filter/Field.h>
#include <strix/client/core/model/manager/filter/TextFilter.h>
#include <strix/client/core/util/ComparisonUtil.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class Like : public Condition {
public:
	STRIX_CLASS(Like, Condition)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.Like")
		STRIX_PROPERTY(m_field)
		STRIX_PROPERTY(m_textFilters)
	)

	typedef std::shared_ptr<Field> FieldPtr;
	typedef std::list<std::shared_ptr<TextFilter> > TextFilterList;

	Like() {}

	Like(FieldPtr field, TextFilterList shared_ptrs) : m_field(std::move(field)), m_textFilters(std::move(shared_ptrs)) {}

	virtual ~Like() {}
	
	const FieldPtr &GetField() const {
		return m_field;
	}

	void SetField(const FieldPtr &field) {
		m_field = field;
	}

	TextFilterList &GetTextFilters(){
		return m_textFilters;
	}

	void SetTextFilters(TextFilterList &textFilters) {
		m_textFilters = textFilters;
	}

	int Compare(const Object &rhs) const override
	{
		const int base = Condition::Compare(rhs);
		if (base != 0)
			return base;

		const Like & other = static_cast<const Like &>(rhs);
		
		const int fieldComp = util::ComparisonUtil::CompareObjectPtr(m_field, other.m_field);
		if (fieldComp != 0)
			return fieldComp;
		
		return util::ComparisonUtil::CompareObjectPtrList(m_textFilters, other.m_textFilters);
	}

private:
	FieldPtr m_field;
	TextFilterList m_textFilters;
};

} } } } } }
