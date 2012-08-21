#include "type_string.hpp"

#include <cstring>
#include <cassert>

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

bool TypeString::is_prefix(const char* prefix) const
{
    std::size_t i = 0;
    while(prefix[i]) {
        if (prefix[i] != value_[i]) {
            return false;
        }
        i++;
    }
    return true;
}

bool TypeString::is_substring(const char* pattern) const
{
    return strstr(value_, pattern) != NULL;
}

bool TypeString::is_smaller(const Type* type) const
{
    const TypeString* v = dynamic_cast<const TypeString*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return strcmp(v->c_str(), value_) > 0;
}

bool TypeString::is_smaller_or_equal(const Type* type) const
{
    const TypeString* v = dynamic_cast<const TypeString*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return strcmp(v->c_str(), value_) >= 0;
}

bool TypeString::is_greater(const Type* type) const
{
    const TypeString* v = dynamic_cast<const TypeString*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return strcmp(v->c_str(), value_) < 0;
}

bool TypeString::is_greater_or_equal(const Type* type) const
{
    const TypeString* v = dynamic_cast<const TypeString*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return strcmp(v->c_str(), value_) <= 0;
}

bool TypeString::equals(const Type* type) const
{
    const TypeString* v = dynamic_cast<const TypeString*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return strcmp(v->c_str(), value_) == 0;
}

const char* TypeString::c_str() const {
    return value_;
}
