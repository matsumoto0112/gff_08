#pragma once

#include <strix/client/core/model/manager/filter/builder/ConditionBuilder.h>

#include <memory>

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter { namespace builder {

class ExpectingFieldClause;
class OrConditionBuilder;
typedef std::shared_ptr<ExpectingFieldClause> ExpectingFieldClausePtr;

class AndConditionBuilder : public ConditionBuilder, public std::enable_shared_from_this<AndConditionBuilder> {
public:
	AndConditionBuilder(std::shared_ptr<ConditionVector> conditions, std::shared_ptr<OrConditionBuilder> parentBuilder);

	AndConditionBuilder(std::shared_ptr<ConditionVector> conditions);

	ExpectingFieldClausePtr Or() override;

	ExpectingFieldClausePtr And() override;

	ConditionPtr Build() override;

private:
	ConditionPtr BuildCondition();

	std::shared_ptr<OrConditionBuilder> m_parentBuilder;
	std::shared_ptr<ExpectingFieldClause> m_andFieldClause;
};

} } } } } } }
