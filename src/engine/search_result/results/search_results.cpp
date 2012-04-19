#include "search_results.hpp"

#include <boost/lexical_cast.hpp>

SearchResults::SearchResults(const QueryParameters& params, const std::vector<const Row*>& results, int count): params(params), results(results), count(count)
{
    //ctor
}

SearchResults::~SearchResults()
{
    //dtor
}


std::string SearchResults::to_string() const
{
    std::string result = "{count:" + Misc::int_to_string( count ) + "," +
    "offset:" + Misc::int_to_string(params.offset) + "," +
    "limit:" + Misc::int_to_string(params.limit) + ",";
    if (params.order_by.size() > 0) {
        result += "order_by:";
        result += (params.order_by[0].second == QueryParameters::ASC ? "+" : "-");
        result += params.order_by[0].first;
        result += ",";
    }

    result += "results:{";
    for(std::size_t i=0; i<results.size(); i++) {
        if (i != 0) result+=",";
        result += results[i]->to_json();
    }
    result += "}}";
    return result;
}

int SearchResults::get_status_code() const {
    return 200;
}
