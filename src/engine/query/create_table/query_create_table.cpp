#include <boost/algorithm/string/predicate.hpp>
#include <iostream>

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


bool QueryCreateTable::set(const std::string& request)
{
  Query::set(request);
  return table_definition.create_table_from_request(request);
}

Query* QueryCreateTable::parse(const std::string& request) const
{
    if (boost::starts_with(request, HTTP_PREFIX)) {
        QueryCreateTable* result = new QueryCreateTable();
        if (result->set(request)) {
          return result;
        }
        delete result;
    }

    return NULL;
}


bool QueryCreateTable::is_modyfing_data() const
{
    return true;
}

TableDefinition QueryCreateTable::get_table_definition() const
{
    return table_definition;
}

std::string QueryCreateTable::get_table_name() const
{
    return table_definition.get_table_name();
}
