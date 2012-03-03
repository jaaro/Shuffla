#include "query_create.hpp"
#include "insert/query_insert.hpp"

QueryCreate::QueryCreate()
{
    register_handler(new QueryInsert());
}

QueryCreate::~QueryCreate()
{
    //dtor
}

void QueryCreate::register_handler(Query* handler)
{
    handlers_list.push_back(handler);
}


Query* QueryCreate::parse_query(const std::string& request) const
{
    for(std::size_t i=0; i<handlers_list.size(); i++) {
        Query* result = handlers_list[i]->parse(request);
        if (result != NULL) {
            return result;
        }
    }
    return NULL;
}
