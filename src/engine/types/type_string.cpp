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

bool TypeString::equals(const std::string& v) const
{
    return v == value;
}

bool TypeString::is_prefix(const std::string& prefix) const
{
    if (prefix.size() > value.size()) return false;
    return value.substr(0, prefix.size()) == prefix;
}


bool TypeString::is_smaller(const std::string& v) const
{
    return v > value;
}

bool TypeString::is_smaller_or_equal(const std::string& v) const
{
    return v >= value;
}

bool TypeString::is_greater(const std::string& v) const
{
    return v < value;
}

bool TypeString::is_greater_or_equal(const std::string& v) const
{
    return v <= value;
}
