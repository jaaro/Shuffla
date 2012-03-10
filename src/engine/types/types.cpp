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

Types::Type Types::string_to_type(const std::string& type) const
{
    if (type == "int" || type == "integer" || type == "long") {
        return Type::Int;
    }
    return Type::String;
}


bool Types::is_correct_value(const Type& type, const std::string& value) const
{
    switch(type) {
    case String:
        return true;
    case Int:
        try {
            boost::lexical_cast<TypeInt::TYPE>( value );
            return true;
        } catch( const boost::bad_lexical_cast & ) {
            return false;
        }
    default:
        //TODO log error
        return false;
    }
}
