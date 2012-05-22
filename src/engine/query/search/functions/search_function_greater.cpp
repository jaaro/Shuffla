#include "search_function_greater.hpp"

#include "../../../types/type.hpp"

SearchFunctionGreater::SearchFunctionGreater()
{
    //ctor
}

SearchFunctionGreater::~SearchFunctionGreater()
{
    //dtor
}

bool SearchFunctionGreater::is_matching(const Row* row) const
{
    const Type* type = row->get_value(get_property_name());

    if (type == NULL) return false;
    return type->is_greater(get_value());
}

bool SearchFunctionGreater::is_available_for_type(const Type* type) const
{
    return true;
}

SearchFunction* SearchFunctionGreater::clone() const
{
    return new SearchFunctionGreater(*this);
}

bool SearchFunctionGreater::is_correct_prefix(const std::string& prefix) const
{
    return prefix == "GREATER" || prefix == "BIGGER";
}
