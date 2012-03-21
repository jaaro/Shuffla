#include "search_function.hpp"

SearchFunction::SearchFunction()
{
    //ctor
}

SearchFunction::~SearchFunction()
{
    //dtor
}


bool SearchFunction::set_value(const std::string& v)
{
    value = v;
    return true;
}

std::string SearchFunction::get_value() const
{
    return value;
}

bool SearchFunction::set_property_name(const std::string& v)
{
    if (!Misc::is_possible_property_name(v)) {
        return false;
    }
    property_name = v;
    return true;
}

std::string SearchFunction::get_property_name() const
{
    return property_name;
}
