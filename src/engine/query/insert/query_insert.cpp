#include <boost/algorithm/string/predicate.hpp>
#include <iostream>

#include "query_insert.hpp"


const std::string QueryInsert::HTTP_PREFIX = "/insert/";

QueryInsert::QueryInsert()
{
    //ctor
}

QueryInsert::~QueryInsert()
{
    //dtor
}

bool QueryInsert::set(const std::string& request)
{
    Query::set(request);
    return parsed_row.set(request.substr(HTTP_PREFIX.size()));
}

Query* QueryInsert::parse(const std::string& request) const
{
    if (boost::starts_with(request, HTTP_PREFIX)) {
        QueryInsert* result = new QueryInsert();
        if (result->set(request)) {
            return result;
        }
        delete result;
    }

    return NULL;
}


bool QueryInsert::is_modyfing_data() const
{
    return true;
}

std::string QueryInsert::get_table_name() const
{
    return parsed_row.get_table_name();
}

DataWithoutTyping QueryInsert::get_parsed_row() const
{
    return parsed_row;
}
