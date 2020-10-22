#pragma once

#include <strix/net/object/Object.h>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {

class Condition : public strix::net::object::Object
{
public:
	STRIX_ABSTRACT_CLASS(Condition, strix::net::object::Object)
	(
		STRIX_CLASS_ID("jp.co.soft_gear.strix.server.core.model.manager.filter.Condition")
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

typedef std::shared_ptr<strix::client::core::model::manager::filter::Condition> ConditionPtr;
typedef std::vector<std::shared_ptr<Condition> > ConditionVector;

} } } } } }
