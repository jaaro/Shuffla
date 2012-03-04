#include "search_result_error.hpp"

SearchResultError::SearchResultError(const std::string& error_message) : error_message(error_message)
{
    //ctor
}

SearchResultError::~SearchResultError()
{
    //dtor
}

std::string SearchResultError::to_string() const
{
    return error_message;
}
