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
