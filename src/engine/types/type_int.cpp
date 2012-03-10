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
