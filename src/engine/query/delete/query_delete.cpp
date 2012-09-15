#include <boost/algorithm/string/predicate.hpp>

#include "query_delete.hpp"

const std::string QueryDelete::HTTP_PREFIX = "/delete/";

QueryDelete::QueryDelete()
{
    //ctor
}

QueryDelete::~QueryDelete()
{
    //dtor
}

bool QueryDelete::set(const std::string& request)
{
    Query::set(request);
    return parsed_query.set(request.substr(HTTP_PREFIX.size()));
}

Query* QueryDelete::parse(const std::string& request) const
{
    if (boost::starts_with(request, HTTP_PREFIX)) {
        QueryDelete* result = new QueryDelete();
        if (result->set(request)) {
            return result;
        }
        delete result;
    }

    return NULL;
}

bool QueryDelete::is_modifying_data() const
{
    return true;
}

std::string QueryDelete::get_table_name() const
{
    return parsed_query.get_table_name();
}

DataWithoutTyping QueryDelete::get_parsed_query() const
{
    return parsed_query;
}
