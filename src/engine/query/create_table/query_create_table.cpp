#include <boost/algorithm/string/predicate.hpp>

#include "query_create_table.hpp"

const std::string QueryCreateTable::HTTP_PREFIX = "/create_table/";

QueryCreateTable::QueryCreateTable()
{
    //ctor
}

QueryCreateTable::~QueryCreateTable()
{
    //dtor
}


QueryCreateTable::QueryCreateTable(const std::string& request)
{
    //ctor
}

Query* QueryCreateTable::parse(const std::string& request) const
{
    if (boost::starts_with(request, HTTP_PREFIX)) {
        return new QueryCreateTable(request);
    }

    return NULL;
}


bool QueryCreateTable::is_modyfing_data() const
{
    return true;
}
