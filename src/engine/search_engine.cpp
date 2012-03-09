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

    if (query->is_modyfing_data()) {
      append_log.append(query);
    }

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
    if (is_table_existing(query->get_table_name())) {
      return new SearchResultError("Table " + query->get_table_name() + " already exists");
    }

    Table* table = new Table();
    table->set_table_definition(query->get_table_definition());
    tables.push_back(table);
    return new SearchResultString("OK: Table created successfully");
}

bool SearchEngine::is_table_existing(const std::string& table_name) const {
    for(std::size_t i=0; i<tables.size(); i++) {
      if (tables[i]->get_table_name() == table_name) {
        return true;
      }
    }
    return false;
}
