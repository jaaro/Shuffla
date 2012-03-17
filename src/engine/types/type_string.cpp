#include "type_string.hpp"

TypeString::TypeString(const TypeString::TYPE value) : value(value)
{
    //ctor
}

TypeString::~TypeString()
{
    //dtor
}

TypeString::TYPE TypeString::get_value() const
{
    return value;
}

std::string TypeString::to_string() const
{
    return value;
}

bool TypeString::is_correct_value(const std::string& value) const
{
    return true;
}

bool TypeString::is_correct_function(const std::string& function_name) const
{
    return false;
}
