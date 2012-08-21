#include "search_function_substring.hpp"
#include "../../../types/type_string.hpp"

SearchFunctionSubstring::SearchFunctionSubstring()
{
    //ctor
}

SearchFunctionSubstring::~SearchFunctionSubstring()
{
    //dtor
}

bool SearchFunctionSubstring::is_matching(const Row* row) const
{
    Type* prop_value = row->get_value(get_property_name());
    TypeString* type = static_cast<TypeString*>(prop_value);
    TypeString* local_value = static_cast<TypeString*>(get_value());

    if (type == NULL) return false;
    if (local_value == NULL) return false;

    return type->is_substring(local_value->c_str());
}

bool SearchFunctionSubstring::is_available_for_type(const Type* type) const
{
    return type->get_name() == "string";
}

SearchFunction* SearchFunctionSubstring::clone() const
{
    return new SearchFunctionSubstring(*this);
}

bool SearchFunctionSubstring::is_correct_prefix(const std::string& prefix) const
{
    return (prefix == "SUBSTR" || prefix == "SUBSTRING");
}
