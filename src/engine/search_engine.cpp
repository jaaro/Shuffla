#include "search_engine.hpp"

SearchEngine::SearchEngine()
{
    //ctor
}

SearchEngine::~SearchEngine()
{
    //dtor
}


std::string SearchEngine::process(const Query& query)
{
    return std::string("modifying = ") + (query.is_modyfing_data() ? "YES" : "NO");
}
