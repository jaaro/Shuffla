#include "search_function_smaller_or_equal.hpp"

#include "search_function_smaller.hpp"
#include "../../../types/type.hpp"

SearchFunctionSmallerOrEqual::SearchFunctionSmallerOrEqual()
{
    //ctor
}

SearchFunctionSmallerOrEqual::~SearchFunctionSmallerOrEqual()
{
    //dtor
}

bool SearchFunctionSmallerOrEqual::is_matching(const Row* row) const
{
    const Type* type = row->get_value(get_property_name());

    if (type == NULL) return false;
    return type->is_smaller_or_equal(get_value());
}

bool SearchFunctionSmallerOrEqual::is_available_for_type(const Type* type) const
{
    return true;
}

SearchFunction* SearchFunctionSmallerOrEqual::clone() const
{
    return new SearchFunctionSmallerOrEqual(*this);
}

bool SearchFunctionSmallerOrEqual::is_correct_prefix(const std::string& prefix) const
{
    return prefix == "SMALLER_OR_EQUAL";
}
