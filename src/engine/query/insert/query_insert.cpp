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
    return true;
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
