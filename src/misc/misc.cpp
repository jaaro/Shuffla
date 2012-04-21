#include "misc.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <cstdio>

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

/**
 * I didn't know what library I should use to decode string
 * I found this source on: http://stackoverflow.com/a/4823686/1256609
 */
std::string Misc::url_decode(const std::string& SRC) {
    std::string ret;
    char ch;
    int ii;
    for (std::size_t i=0; i<SRC.length(); i++) {
        if (int(SRC[i])==37) {
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else {
            ret+=SRC[i];
        }
    }
    return (ret);
}
