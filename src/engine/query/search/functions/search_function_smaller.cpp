#include "search_function_smaller.hpp"
#include "../../../types/type_number.hpp"

SearchFunctionSmaller::SearchFunctionSmaller()
{
    //ctor
}

SearchFunctionSmaller::~SearchFunctionSmaller()
{
    //dtor
}

bool SearchFunctionSmaller::is_matching(const Row* row) const
{
    Type* prop_value = row->get_value(get_property_name());
    TypeNumber* type = static_cast<TypeNumber*>(prop_value);

    if (type == NULL) return false;
    return type->is_smaller(get_value());
}

bool SearchFunctionSmaller::is_available_for_type(const Type* type) const
{
    return type->get_name() == "int" || type->get_name() == "double";
}

SearchFunction* SearchFunctionSmaller::clone() const
{
    return new SearchFunctionSmaller(*this);
}

bool SearchFunctionSmaller::is_correct_prefix(const std::string& prefix) const
{
    return prefix == "SMALLER";
}
