#pragma once

#include <functional>
#include <memory>
#include <string>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter { namespace builder {
	
class ConditionBuilder;
class FieldClauseBuilder;
class ExpectingFieldClause;
typedef std::shared_ptr<ConditionBuilder> ConditionBuilderPtr;
typedef std::shared_ptr<FieldClauseBuilder> FieldClauseBuilderPtr;
typedef std::shared_ptr<ExpectingFieldClause> ExpectingFieldClausePtr;

class ExpectingFieldClause
{	
public:
	ExpectingFieldClause(ConditionBuilderPtr builder);

	FieldClauseBuilderPtr Field(std::string fieldName);

	ConditionBuilderPtr Group(std::function<ConditionBuilderPtr(ExpectingFieldClausePtr)> groupFunction);

private:
	ConditionBuilderPtr m_builder;
};

} } } } } } }

