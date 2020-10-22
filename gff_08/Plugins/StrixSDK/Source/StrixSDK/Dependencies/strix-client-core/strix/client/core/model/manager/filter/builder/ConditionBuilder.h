#pragma once

#include <memory>
#include <vector>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {
class Condition;
typedef std::shared_ptr<Condition> ConditionPtr;
typedef std::vector<ConditionPtr> ConditionVector;
} } } } } }

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter { namespace builder {
	
class FieldClauseBuilder;
class ExpectingFieldClause;
typedef std::shared_ptr<ExpectingFieldClause> ExpectingFieldClausePtr;

class ConditionBuilder {
public:
	friend class FieldClauseBuilder;
	friend class ExpectingFieldClause;

	virtual ~ConditionBuilder() = default;

	static ExpectingFieldClausePtr Builder();

	virtual ExpectingFieldClausePtr Or();

	virtual ExpectingFieldClausePtr And();

	virtual ConditionPtr Build();

protected:
	ConditionBuilder();

	ConditionBuilder(std::shared_ptr<ConditionVector> conditions);

	void AddCondition(ConditionPtr condition);

	std::shared_ptr<ConditionVector> m_conditions;
};

typedef std::shared_ptr<ConditionBuilder> ConditionBuilderPtr;

} } } } } } }

#include <strix/client/core/model/manager/filter/builder/FieldClauseBuilder.h>
#include <strix/client/core/model/manager/filter/builder/OrConditionBuilder.h>
#include <strix/client/core/model/manager/filter/builder/AndConditionBuilder.h>
#include <strix/client/core/model/manager/filter/builder/ExpectingFieldClause.h>

