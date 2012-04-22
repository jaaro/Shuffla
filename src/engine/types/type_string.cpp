#include "type_string.hpp"

#include <cstring>
#include <iostream>

TypeString::TypeString(const TypeString::TYPE value) : value_(new char[value.size() + 1])
{
    strcpy(value_, value.c_str());
}

TypeString::~TypeString()
{
    delete[] value_;
}

Type* TypeString::clone() const
{
    return new TypeString(get_value());
}

TypeString::TYPE TypeString::get_value() const
{
    return value_;
}

std::string TypeString::to_string() const
{
    return value_;
}

bool TypeString::is_correct_value(const std::string& value) const
{
    return true;
}

bool TypeString::equals(const std::string& v) const
{
    return strcmp(value_, v.c_str()) == 0;
}

bool TypeString::is_prefix(const std::string& prefix) const
{
    std::size_t i = 0;
    while(i < prefix.size()) {
        if (prefix[i] != value_[i]) {
            return false;
        }
        i++;
    }
    return true;
}


bool TypeString::is_smaller(const std::string& v) const
{
    return strcmp(v.c_str(), value_) > 0;
}

bool TypeString::is_smaller_or_equal(const std::string& v) const
{
    return strcmp(v.c_str(), value_) >= 0;
}

bool TypeString::is_greater(const std::string& v) const
{
    return strcmp(v.c_str(), value_) < 0;
}

bool TypeString::is_greater_or_equal(const std::string& v) const
{
    return strcmp(v.c_str(), value_) <= 0;
}
