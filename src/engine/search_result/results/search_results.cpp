#include "search_results.hpp"

#include <boost/lexical_cast.hpp>

SearchResults::SearchResults(const std::vector<const Row*> results): results(results)
{
    //ctor
}

SearchResults::~SearchResults()
{
    //dtor
}


std::string SearchResults::to_string() const
{
    std::string result = "{count:" + boost::lexical_cast<std::string>( results.size() ) + ",results:{";
    for(std::size_t i=0; i<results.size(); i++) {
        if (i != 0) result+=",";
        result += results[i]->to_json();
    }
    result += "}}";
    return result;
}
