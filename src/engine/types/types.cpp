#include <boost/lexical_cast.hpp>

#include "types.hpp"
#include "type_string.hpp"
#include "type_int.hpp"
#include "type_double.hpp"

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
    if (type == "int" || type == "integer") {
        return true;
    }
    if (type == "string" || type =="varchar" || type == "text") {
        return true;
    }
    if (type == "double") {
        return true;
    }
    return false;
}

Type* Types::string_to_type(const std::string& type) const
{
    if (type == "int" || type == "integer") {
        return new TypeInt(0);
    } else if (type == "string" || type =="varchar" || type == "text") {
        return new TypeString("");
    } else if (type == "double") {
        return new TypeDouble(0.0);
    }
    return false;
}


bool Types::is_correct_value(const Type* type, const std::string& value) const
{
    return type->is_correct_value(value);
}
