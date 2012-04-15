#include "query_create.hpp"
#include "insert/query_insert.hpp"
#include "search/query_search.hpp"
#include "delete/query_delete.hpp"
#include "drop_table/query_drop_table.hpp"
#include "create_table/query_create_table.hpp"

QueryCreate::QueryCreate()
{
    register_handler(new QuerySearch());
    register_handler(new QueryInsert());
    register_handler(new QueryDelete());
    register_handler(new QueryCreateTable());
    register_handler(new QueryDropTable());
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
