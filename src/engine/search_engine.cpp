#include "search_engine.hpp"
#include "search_result/errors/search_result_error.hpp"
#include "search_result/string/search_result_string.hpp"
#include "../storage/row/row.hpp"

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

    //temporary
    if (query->is_modyfing_data()) {
        save_dump();
    }

    return result;
}

void SearchEngine::processing_query_begin(const Query* query) {}
void SearchEngine::processing_query_end(const Query* query) {}

SearchResult* SearchEngine::process_insert(const QueryInsert* query)
{
    Table* table = find_table(query->get_table_name());
    if (table == NULL) {
        return new SearchResultError("Table " + query->get_table_name() + " doesn't exists");
    }

    bool success = query->get_parsed_row().is_matching_table_definition(table->get_table_definition());

    if (!success) {
        return new SearchResultError("Error during insert. Row doesn't match table definition. Check logs for more details.\nRequest + " + query->to_string());
    }

    Row* new_row = new Row(table->get_table_definition(), query->get_parsed_row());
    table->insert(new_row);
    return new SearchResultString("OK");
}

SearchResult* SearchEngine::process_search(const QuerySearch* query)
{
    return new SearchResultString("Search");
}
SearchResult* SearchEngine::process_create_table(const QueryCreateTable* query)
{
    if (find_table(query->get_table_name()) != NULL) {
        return new SearchResultError("Table " + query->get_table_name() + " already exists");
    }

    Table* table = new Table();
    table->set_table_definition(query->get_table_definition());
    tables.push_back(table);
    return new SearchResultString("OK: Table created successfully");
}

Table* SearchEngine::find_table(const std::string& table_name) const
{
    for(std::size_t i=0; i<tables.size(); i++) {
        if (tables[i]->get_table_name() == table_name) {
            return tables[i];
        }
    }
    return NULL;
}

bool SearchEngine::save_dump() const
{
    //TODO, tu powinien być mutex na wszystko ?
    DumpProcessor dump_processor;
    for(std::size_t i=0; i<tables.size(); i++) {
        tables[i]->dump_table(dump_processor);
    }

    return true;
}
