#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>

#include "query_drop_table.hpp"

const std::string QueryDropTable::HTTP_PREFIX = "/drop_table/";

QueryDropTable::QueryDropTable()
{
    //ctor
}

QueryDropTable::~QueryDropTable()
{
    //dtor
}

bool QueryDropTable::set(const std::string& request)
{
    Query::set(request);
    table_name = request.substr(HTTP_PREFIX.size());
    return true;
}

Query* QueryDropTable::parse(const std::string& request) const
{
    if (boost::starts_with(request, HTTP_PREFIX)) {
        QueryDropTable* result = new QueryDropTable();
        if (result->set(request)) {
            return result;
        }
        delete result;
    }

    return NULL;
}

bool QueryDropTable::is_modifying_data() const
{
    return true;
}

std::string QueryDropTable::get_table_name() const
{
    return table_name;
}
