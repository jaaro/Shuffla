#include "search_function.hpp"

SearchFunction::SearchFunction()
{
    //ctor
}

SearchFunction::~SearchFunction()
{
    //TODO
    //delete value;
}


bool SearchFunction::set_value(const Type* type, const std::string& v)
{
    if (type->get_name() == "int") {
        value = new TypeInt(v);
    } else if (type->get_name() == "string") {
        value = new TypeString(v);
    } else if (type->get_name() == "double") {
        value = new TypeDouble(v);
    }

    return true;
}

Type* SearchFunction::get_value() const
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
