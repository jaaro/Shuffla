#include <boost/lexical_cast.hpp>

#include "types.hpp"
#include "type_string.hpp"
#include "type_int.hpp"

Types::Types()
{
    //ctor
}

Types::~Types()
{
    //dtor
}


bool Types::is_correct_type(const std::string& type) const
{
    if (type == "int" || type == "integer" || type == "long") {
        return true;
    }
    if (type == "string" || type =="varchar" || type == "text") {
        return true;
    }
    return false;
}

Type* Types::string_to_type(const std::string& type) const
{
    //TODO check for memory leaks
    if (type == "int" || type == "integer" || type == "long") {
        return new TypeInt(0);
    }
    if (type == "string" || type =="varchar" || type == "text") {
        return new TypeString("");
    }
    return false;
}


bool Types::is_correct_value(const Type* type, const std::string& value) const
{
    return type->is_correct_value(value);
}
