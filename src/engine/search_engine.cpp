#include "search_engine.hpp"
#include "search_result/errors/search_result_error.hpp"
#include "search_result/string/search_result_string.hpp"

SearchEngine::SearchEngine()
{
    //ctor
}

SearchEngine::~SearchEngine()
{
    //dtor
}


SearchResult* SearchEngine::process_query(const Query* query)
{
    processing_query_begin(query);
    SearchResult* result;

    if (dynamic_cast<const QueryInsert*>(query) != NULL) {
        result = process_insert( dynamic_cast<const QueryInsert*>(query) );
    } else if (dynamic_cast<const QuerySearch*>(query) != NULL) {
        result = process_search( dynamic_cast<const QuerySearch*>(query) );
    } else if (dynamic_cast<const QueryCreateTable*>(query) != NULL) {
        result = process_create_table( dynamic_cast<const QueryCreateTable*>(query) );
    } else {
        result = new SearchResultError("Shuffla error: Not supported operation. Please install latest version of shuffla.");
    }

    processing_query_end(query);
    return result;
}

void SearchEngine::processing_query_begin(const Query* query) {}
void SearchEngine::processing_query_end(const Query* query) {}

SearchResult* SearchEngine::process_insert(const QueryInsert* query)
{
    return new SearchResultString("insert");
}
SearchResult* SearchEngine::process_search(const QuerySearch* query)
{
    return new SearchResultString("search");
}
SearchResult* SearchEngine::process_create_table(const QueryCreateTable* query)
{
    return new SearchResultString("create_table");
}
