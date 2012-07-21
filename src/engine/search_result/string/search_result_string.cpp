#include "search_result_string.hpp"

SearchResultString::SearchResultString(const std::string& text) : text(text)
{
    //ctor
}

SearchResultString::~SearchResultString()
{
    //dtor
}

std::string SearchResultString::to_string() const
{
    return text;
}


int SearchResultString::get_status_code() const
{
    return 200;
}
