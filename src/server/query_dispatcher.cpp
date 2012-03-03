#include <cstdio>

#include "query_dispatcher.hpp"

QueryDispatcher::QueryDispatcher(SearchEngine* search_engine) : search_engine(search_engine)
{
    // right now  nothing
    // but it will change in the future
}

QueryDispatcher::~QueryDispatcher()
{
    // intensionally nothing
}

std::string QueryDispatcher::process_query(const std::string& request)
{
    // request contains request parameters
    // so if user requests localhost:3000/this/is/cool
    // request is equal "/this/is/cool"

    printf("%s\n", request.c_str());

    Query* query = query_parser.parse_query(request);
    if (query == NULL) {
      return "Error: Unknown request format. Unable to parse " + request;
    }

    return search_engine->process(*query);
}
