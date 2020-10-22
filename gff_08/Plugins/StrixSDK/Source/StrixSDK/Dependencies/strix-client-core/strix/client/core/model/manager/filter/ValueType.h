#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class ValueType : public strix::net::object::Object
{
public:
	STRIX_ABSTRACT_CLASS(ValueType, Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.ValueType")
	)

	int Compare(const Object &rhs) const override
	{
		const net::object::MetaClass &metaClass = GetMetaClass();
		const net::object::MetaClass &metaClass2 = rhs.GetMetaClass();
	
		if (&metaClass > &metaClass2)
			return 1;
		if (&metaClass < &metaClass2)
			return -1;
		
		return 0;
	}
};

typedef std::shared_ptr<ValueType> ValueTypePtr;

} } } } } }
