#include "search_function_greater_or_equal.hpp"

#include "../../../types/type.hpp"

SearchFunctionGreaterOrEqual::SearchFunctionGreaterOrEqual()
{
    //ctor
}

SearchFunctionGreaterOrEqual::~SearchFunctionGreaterOrEqual()
{
    //dtor
}

bool SearchFunctionGreaterOrEqual::is_matching(const Row* row) const
{
    Type* type = row->get_value(get_property_name());

    if (type == NULL) return false;
    return type->is_greater_or_equal(get_value());
}

bool SearchFunctionGreaterOrEqual::is_available_for_type(const Type* type) const
{
    return true;
}

SearchFunction* SearchFunctionGreaterOrEqual::clone() const
{
    return new SearchFunctionGreaterOrEqual(*this);
}

bool SearchFunctionGreaterOrEqual::is_correct_prefix(const std::string& prefix) const
{
    return prefix == "GREATER_OR_EQUAL" || prefix == "BIGGER_OR_EQUAL";
}
