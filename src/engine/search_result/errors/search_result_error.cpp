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

int SearchResultError::get_status_code() const {
    return 400;
}
