#include <boost/lexical_cast.hpp>

#include "type_int.hpp"

TypeInt::TypeInt(const TypeInt::TYPE value) : value(value)
{
    // intensionally nothing
}

TypeInt::TypeInt(const std::string& number) : value (boost::lexical_cast<TypeInt::TYPE>( number ))
{
    // intensionally nothing
}

TypeInt::~TypeInt()
{
    //dtor
}


TypeInt::TYPE TypeInt::get_value() const
{
    return value;
}


std::string TypeInt::to_string() const
{
    return boost::lexical_cast<std::string>( value );
}

bool TypeInt::is_correct_value(const std::string& value) const
{
    try {
        int res = boost::lexical_cast<TypeInt::TYPE>( value );
        return true;
    } catch(std::exception e) {
        return false;
    }
}

bool TypeInt::is_correct_function(const std::string& function_name) const
{
    return false;
}
