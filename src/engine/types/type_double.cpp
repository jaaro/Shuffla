#include <boost/lexical_cast.hpp>

#include "type_double.hpp"

TypeDouble::TypeDouble(const TypeDouble::TYPE value) : value(value)
{
    // intensionally nothing
}

TypeDouble::TypeDouble(const std::string& number) : value (boost::lexical_cast<TypeDouble::TYPE>( number ))
{
    // intensionally nothing
}

TypeDouble::~TypeDouble()
{
    //dtor
}


TypeDouble::TYPE TypeDouble::get_value() const
{
    return value;
}


std::string TypeDouble::to_string() const
{
    return boost::lexical_cast<std::string>( value );
}

bool TypeDouble::is_correct_value(const std::string& value) const
{
    try {
        boost::lexical_cast<TypeDouble::TYPE>( value );
        return true;
    } catch(std::exception e) {
        return false;
    }
}

bool TypeDouble::is_correct_function(const std::string& function_name) const
{
    return false;
}

bool TypeDouble::equals(const std::string& v) const
{
    return is_correct_value(v) && boost::lexical_cast<TypeDouble::TYPE>( v ) == value;
}

bool TypeDouble::is_smaller(const std::string& v) const
{
    return is_correct_value(v) && boost::lexical_cast<TypeDouble::TYPE>( v ) > value;
}

bool TypeDouble::is_smaller_or_equal(const std::string& v) const
{
    return is_correct_value(v) && boost::lexical_cast<TypeDouble::TYPE>( v ) >= value;
}

bool TypeDouble::is_bigger(const std::string& v) const
{
    return is_correct_value(v) && boost::lexical_cast<TypeDouble::TYPE>( v ) < value;
}

bool TypeDouble::is_bigger_or_equal(const std::string& v) const
{
    return is_correct_value(v) && boost::lexical_cast<TypeDouble::TYPE>( v ) <= value;
}
