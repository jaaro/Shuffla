#include "search_function_equal.hpp"

SearchFunctionEqual::SearchFunctionEqual()
{
    //ctor
}

SearchFunctionEqual::~SearchFunctionEqual()
{
    //dtor
}

SearchFunctionEqual::SearchFunctionEqual(const SearchFunctionEqual& fun)
{
    property_name = fun.get_property_name();
    value = fun.value;
}


bool SearchFunctionEqual::is_matching(const Row* row) const
{
    return row->get_value(property_name)->equals(value);
}

bool SearchFunctionEqual::set(const std::string& name)
{
    if (!Misc::is_possible_property_name(name)) {
        return false;
    }
    property_name = name;
    return true;
}

bool SearchFunctionEqual::is_available_for_type(const Type* type) const
{
    return true;
}

SearchFunction* SearchFunctionEqual::clone() const
{
    SearchFunctionEqual* res = new SearchFunctionEqual(*this);
    return res;
}
