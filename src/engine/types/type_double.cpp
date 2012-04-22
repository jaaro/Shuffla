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

Type* TypeDouble::clone() const
{
    return new TypeDouble(value);
}

TypeDouble::TYPE TypeDouble::get_value() const
{
    return value;
}


std::string TypeDouble::to_string() const
{
    return Misc::double_to_string( value );
}

bool TypeDouble::is_correct_value(const std::string& value) const
{
    return Misc::can_be_parsed_to_double(value);
}

bool TypeDouble::equals(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_double( v ) == value;
}

bool TypeDouble::is_smaller(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_double( v ) > value;
}

bool TypeDouble::is_smaller_or_equal(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_double( v ) >= value;
}

bool TypeDouble::is_greater(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_double( v ) < value;
}

bool TypeDouble::is_greater_or_equal(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_double( v ) <= value;
}
