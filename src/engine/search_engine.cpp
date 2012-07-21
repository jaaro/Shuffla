#include "search_engine.hpp"
#include "search_result/errors/search_result_error.hpp"
#include "search_result/string/search_result_string.hpp"
#include "storage/row.hpp"
#include "query/search/query_parameters.hpp"
#include "../dump/save_dump_manager.hpp"
#include "../dump/dump_saver.hpp"

SearchEngine::SearchEngine(DumpLoader& dump_loader)
{
    while(!dump_loader.is_eof()) {
        tables.push_back(new Table(dump_loader));
    }
    dump_loader.close();
}

SearchEngine::SearchEngine()
{
    //dtor
}

SearchEngine::~SearchEngine()
{
    for(std::size_t i=0; i< tables.size(); i++) {
        delete tables[i];
    }
}


SearchResult* SearchEngine::process_query(const Query* query)
{
    processing_query_begin(query);
    SearchResult* result;

    if (query->is_modyfing_data()) {
        append_log.append(query);
        SaveDumpManager::getInstance().add_modifying_command();
    }

    if (dynamic_cast<const QueryInsert*>(query) != NULL) {
        result = process_insert( dynamic_cast<const QueryInsert*>(query) );
    } else if (dynamic_cast<const QuerySearch*>(query) != NULL) {
        result = process_search( dynamic_cast<const QuerySearch*>(query) );
    } else if (dynamic_cast<const QueryDelete*>(query) != NULL) {
        result = process_delete( dynamic_cast<const QueryDelete*>(query) );
    } else if (dynamic_cast<const QueryCreateTable*>(query) != NULL) {
        result = process_create_table( dynamic_cast<const QueryCreateTable*>(query) );
    } else if (dynamic_cast<const QueryDropTable*>(query) != NULL) {
        result = process_drop_table( dynamic_cast<const QueryDropTable*>(query) );
    } else {
        result = new SearchResultError("Shuffla error: Not supported operation. Please install latest version of shuffla.");
    }

    processing_query_end(query);

    return result;
}

void SearchEngine::processing_query_begin(const Query* query) {}
void SearchEngine::processing_query_end(const Query* query) {}

/**
 * Processes insert command.
 *
 * It means that for given QueryInsert this function:
 * -> finds table that insert command refers to
 * -> checks, if insert data matches table definition
 * -> handles error from above points
 * -> creates new row, based on given data
 * -> passes new row to table class
 */
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


/**
 * Processes search command
 *
 * It means that for given QuerySearch this function:
 * -> finds table that search command refers to
 * -> checks, if search command matches table definition
 * -> handles error from above points
 * ->
 */
SearchResult* SearchEngine::process_search(const QuerySearch* query)
{
    Table* table = find_table(query->get_table_name());
    if (table == NULL) {
        return new SearchResultError("Table " + query->get_table_name() + " doesn't exists");
    }

    boost::shared_ptr<QueryParameters> params( new QueryParameters);
    bool success = params->set(table->get_table_definition(), query->get_parsed_query());

    if (!success) {
        return new SearchResultError("Error during insert. Row doesn't match table definition. Check logs for more details.\nRequest + " + query->to_string());
    }

    return table->search(params);
}

/**
 * Processes delete query
 *
 * It means that for given QueryDelete this function:
 * -> finds table that delete command refers to
 * -> checks, if delete command matches table definition
 * -> handles error from above points
 * ->
 */
SearchResult* SearchEngine::process_delete(const QueryDelete* query)
{
    Table* table = find_table(query->get_table_name());
    if (table == NULL) {
        return new SearchResultError("Table " + query->get_table_name() + " doesn't exists");
    }

    boost::shared_ptr<QueryParameters> params( new QueryParameters);
    bool success = params->set(table->get_table_definition(), query->get_parsed_query());

    if (!success) {
        return new SearchResultError("Error during delete. Row doesn't match table definition. Check logs for more details.\nRequest + " + query->to_string());
    }

    int count = table->remove(params);

    return new SearchResultString("Removed " + Misc::int_to_string(count) + " rows");
}

/**
 * Processes create table command
 *
 * It means that for given QueryCreateTable this function:
 * -> checks if such table already exists
 * -> creates table
 *
 */
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

/**
 * Processes drop table command
 *
 * It means that for given QueryDropTable this function:
 * -> checks if such table already exists
 * -> drops table
 * -> releases memory
 *
 */
SearchResult* SearchEngine::process_drop_table(const QueryDropTable* query)
{
    for(std::vector<Table*>::iterator it = tables.begin(); it != tables.end(); it++) {
        if ((*it)->get_table_name() == query->get_table_name()) {
            tables.erase(it);
            Table* to_remove = *it;
            delete to_remove;
            return new SearchResultString("Drop table successfull.");
        }
    }

    return new SearchResultError("Drop Table: Table " + query->get_table_name() + " doesn't exists");
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
    std::cout << "Start saving database\n";
    DumpSaver dump_saver;
    for(std::size_t i=0; i<tables.size(); i++) {
        if (i > 0) dump_saver.append("\n");
        tables[i]->dump_table(dump_saver);
    }
    std::cout << "Saving ended successfully\n";

    return true;
}
