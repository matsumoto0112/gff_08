#pragma once

#include <memory>
#include <string>
#include <vector>

namespace strix { namespace net { namespace object {
class ObjectAdapter;
} } }

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter {
class Field;
typedef std::shared_ptr<Field> FieldPtr;
} } } } } }

namespace strix { namespace client { namespace core { namespace model { namespace manager { namespace filter { namespace builder {

class ConditionBuilder;
typedef std::shared_ptr<ConditionBuilder> ConditionBuilderPtr;

class FieldClauseBuilder
{
public:
	FieldClauseBuilder(ConditionBuilderPtr builder, FieldPtr field);
	
	ConditionBuilderPtr EqualTo(const net::object::ObjectAdapter &value);

	ConditionBuilderPtr EqualTo(const FieldPtr &otherField);

	ConditionBuilderPtr NotEqualTo(const net::object::ObjectAdapter &value);

	ConditionBuilderPtr NotEqualTo(const FieldPtr &otherField);

	ConditionBuilderPtr GreaterThan(const net::object::ObjectAdapter &value);

	ConditionBuilderPtr GreaterThanEquals(const net::object::ObjectAdapter &value);

	ConditionBuilderPtr LessThan(const net::object::ObjectAdapter &value);

	ConditionBuilderPtr LessThanEquals(const net::object::ObjectAdapter &value);

	ConditionBuilderPtr GreaterThan(const FieldPtr &otherField);

	ConditionBuilderPtr GreaterThanEquals(const FieldPtr &otherField);

	ConditionBuilderPtr LessThan(const FieldPtr &otherField);

	ConditionBuilderPtr LessThanEquals(const FieldPtr &otherField);

	ConditionBuilderPtr BetweenExclusive(const net::object::ObjectAdapter &lowerBound, const net::object::ObjectAdapter &upperBound);

	ConditionBuilderPtr BetweenInclusive(const net::object::ObjectAdapter &lowerBound, const net::object::ObjectAdapter &upperBound);

	ConditionBuilderPtr Like(std::vector<net::object::ObjectAdapter> tokens);

	ConditionBuilderPtr StartsWith(std::string prefix);

	ConditionBuilderPtr EndsWith(std::string suffix);

	ConditionBuilderPtr Contains(std::string text);

	ConditionBuilderPtr SurroundedBy(std::string leftSide, std::string rightSide);

	ConditionBuilderPtr In(std::vector<net::object::ObjectAdapter> values);

	ConditionBuilderPtr IsNull();

	ConditionBuilderPtr IsNotNull();

private:
	FieldPtr m_field;
	ConditionBuilderPtr m_builder;
};

} } } } } } }
