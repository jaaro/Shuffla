#include "search_function_with_prefix.hpp"

SearchFunctionWithPrefix::SearchFunctionWithPrefix()
{
    //ctor
}

SearchFunctionWithPrefix::~SearchFunctionWithPrefix()
{
    //dtor
}


bool SearchFunctionWithPrefix::set(const std::string& name)
{
    size_t pos_open = name.find('(');
    size_t pos_end = name.find(')');

    if (pos_open == std::string::npos || pos_end + 1 != name.size()) {
        return false;
    }
    if (!is_correct_prefix(name.substr(0, pos_open))) {
        return false;
    }

    if (!set_property_name(name.substr(pos_open + 1, pos_end - pos_open - 1))) {
        return false;
    }

    return true;
}
