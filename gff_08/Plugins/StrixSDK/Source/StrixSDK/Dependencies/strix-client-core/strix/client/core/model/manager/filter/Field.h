#pragma once

#include <strix/net/object/Object.h>
#include <strix/client/core/model/manager/filter/ValueType.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class Field : public ValueType {
public:
	STRIX_CLASS(Field, ValueType)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.Field")
		STRIX_PROPERTY(m_fieldName)
	)


	Field() {}
	
    Field(const std::string &fieldName) {
		m_fieldName = fieldName;
    }
	
	virtual ~Field() {}

	std::string &GetFieldName() {
		return m_fieldName;
	}

	void SetFieldName(const std::string &fieldName) {
		m_fieldName = fieldName;
	}

	int Compare(const Object &rhs) const override
	{
		const int base = ValueType::Compare(rhs);
		if (base != 0)
			return base;

		const Field &other = static_cast<const Field &>(rhs);
		if (m_fieldName > other.m_fieldName)
			return 1;
		if (m_fieldName < other.m_fieldName)
			return -1;

		return 0;
	}
private:
	std::string m_fieldName;
};

typedef std::shared_ptr<Field> FieldPtr;

} } } } } }
