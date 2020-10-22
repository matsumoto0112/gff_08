#pragma once

#include <strix/client/core/model/manager/filter/builder/ConditionBuilder.h>

#include <memory>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter { namespace builder {

class ExpectingFieldClause;
typedef std::shared_ptr<ExpectingFieldClause> ExpectingFieldClausePtr;

class OrConditionBuilder : public ConditionBuilder, public std::enable_shared_from_this<OrConditionBuilder> {
public:
	OrConditionBuilder(std::shared_ptr<ConditionVector> conditions);

	void AddBaseCondition(ConditionPtr condition);

	ExpectingFieldClausePtr Or() override;

	ExpectingFieldClausePtr And() override;

	ConditionPtr Build() override;

protected:
	std::shared_ptr<ConditionVector> m_baseConditions;
	ExpectingFieldClausePtr m_orFieldClause;
};

} } } } } } }

