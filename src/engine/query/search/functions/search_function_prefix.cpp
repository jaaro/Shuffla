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

bool SearchFunctionPrefix::is_matching(const Row* row) const
{
    Type* prop_value = row->get_value(get_property_name());
    TypeString* type = static_cast<TypeString*>(prop_value);
    TypeString* local_value = static_cast<TypeString*>(get_value());

    if (type == NULL) return false;
    if (local_value == NULL) return false;





    return type->is_prefix(local_value->c_str());
}

bool SearchFunctionPrefix::is_available_for_type(const Type* type) const
{
    return type->get_name() == "string";
}

SearchFunction* SearchFunctionPrefix::clone() const
{
    return new SearchFunctionPrefix(*this);
}

bool SearchFunctionPrefix::is_correct_prefix(const std::string& prefix) const
{
    return (prefix == "PREFIX" || prefix == "STARTS_WITH"|| prefix == "SUBSTR" || prefix == "SUBSTRING");
}
