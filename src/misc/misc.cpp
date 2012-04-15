#include "misc.hpp"

#include <boost/lexical_cast.hpp>

Misc::Misc()
{
    //ctor
}

Misc::~Misc()
{
    //dtor
}



int Misc::string_to_int(const std::string& value)
{
    return boost::lexical_cast<int>( value );
}

std::string Misc::int_to_string(const int value)
{
    return boost::lexical_cast<std::string>( value );
}


double Misc::string_to_double(const std::string& value)
{
    return boost::lexical_cast<double>( value );
}


std::string Misc::double_to_string(const double value)
{
    return boost::lexical_cast<std::string>( value );
}


bool Misc::is_possible_property_name(const std::string& value)
{
    for(std::size_t i=0; i<value.size(); i++) {
        if (!isalnum(value[i]) && value[i] != '_') return false;
    }
    return value.size() > 0 && value != "ORDER_BY" && value != "LIMIT" && value != "OFFSET";
}


bool Misc::can_be_parsed_to_int(const std::string& value)
{
    try {
        boost::lexical_cast<int>( value );
        return true;
    } catch(std::exception e) {
        return false;
    }
}

bool Misc::can_be_parsed_to_double(const std::string& value)
{
    try {
        boost::lexical_cast<double>( value );
        return true;
    } catch(std::exception e) {
        return false;
    }
}
