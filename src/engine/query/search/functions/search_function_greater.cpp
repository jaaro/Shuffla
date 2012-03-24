#include "search_function_greater.hpp"

#include "../../../types/type_number.hpp"

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
    Type* prop_value = row->get_value(get_property_name());
    TypeNumber* type = static_cast<TypeNumber*>(prop_value);

    if (type == NULL) return false;
    return type->is_greater(get_value());
}

bool SearchFunctionGreater::is_available_for_type(const Type* type) const
{
    return type->get_name() == "int" || type->get_name() == "double";
}

SearchFunction* SearchFunctionGreater::clone() const
{
    return new SearchFunctionGreater(*this);
}

bool SearchFunctionGreater::is_correct_prefix(const std::string& prefix) const
{
    return prefix == "GREATER" || prefix == "BIGGER";
}
