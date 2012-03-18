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

bool SearchFunction::set_property_name(const std::string& v)
{
    //TODO check if v is correct property name
    property_name = v;
    return true;
}

std::string SearchFunction::get_property_name() const
{
    return property_name;
}
