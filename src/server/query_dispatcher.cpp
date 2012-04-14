#include <cstdio>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "query_dispatcher.hpp"
#include "../engine/search_result/search_result.hpp"
#include "../misc/slow_log.hpp"

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

    //TODO second_clock means that id doesn't have miliseconds precision.
    boost::posix_time::ptime t1 = boost::posix_time::second_clock::local_time();

    SearchResult* result = search_engine->process_query(query);
    std::string ret = result->to_string();

    boost::posix_time::ptime t2 = boost::posix_time::second_clock::local_time();
    boost::posix_time::time_duration diff = t2 - t1;


    SlowLog::getInstance().log(diff.total_milliseconds(), request);

    delete result;
    return ret;
}
