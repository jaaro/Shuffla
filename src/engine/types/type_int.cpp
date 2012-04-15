#include "type_int.hpp"

TypeInt::TypeInt(const TypeInt::TYPE value) : value(value)
{
    // intensionally nothing
}

TypeInt::TypeInt(const std::string& number) : value (Misc::string_to_int( number ))
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
    return Misc::int_to_string( value );
}

bool TypeInt::is_correct_value(const std::string& value) const
{
    return Misc::can_be_parsed_to_int(value);
}

bool TypeInt::is_correct_function(const std::string& function_name) const
{
    return false;
}

bool TypeInt::equals(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_int( v ) == value;
}

bool TypeInt::is_smaller(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_int( v ) > value;
}

bool TypeInt::is_smaller_or_equal(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_int( v ) >= value;
}

bool TypeInt::is_greater(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_int( v ) < value;
}

bool TypeInt::is_greater_or_equal(const std::string& v) const
{
    return is_correct_value(v) && Misc::string_to_int( v ) >= value;
}
