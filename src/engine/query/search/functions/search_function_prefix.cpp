#include "search_function_prefix.hpp"
#include "../../../types/type_string.hpp"

SearchFunctionPrefix::SearchFunctionPrefix()
{
    //ctor
}

SearchFunctionPrefix::~SearchFunctionPrefix()
{
    //dtor
}

SearchFunctionPrefix::SearchFunctionPrefix(const SearchFunctionPrefix& fun)
{
    property_name = fun.property_name;
    value = fun.value;
}

bool SearchFunctionPrefix::is_matching(const Row* row) const
{
    Type* prop_value = (*row)[property_name];
    TypeString* type = static_cast<TypeString*>(prop_value);

    if (type == NULL) return false;
    return type->is_prefix(value);
}

bool SearchFunctionPrefix::is_available_for_type(const Type* type) const
{
    return type->get_name() == "string";
}

SearchFunction* SearchFunctionPrefix::clone() const
{
    SearchFunctionPrefix* res = new SearchFunctionPrefix(*this);
    return res;
}

bool SearchFunctionPrefix::is_correct_prefix(const std::string& prefix) const
{
    return (prefix == "PREFIX" || prefix == "STARTS_WITH"|| prefix == "SUBSTR" || prefix == "SUBSTRING");
}
