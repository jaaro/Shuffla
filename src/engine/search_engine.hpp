#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>

#include "query/query.hpp"
#include "query/insert/query_insert.hpp"
#include "query/search/query_search.hpp"
#include "query/create_table/query_create_table.hpp"
#include "table/table.hpp"
#include "search_result/search_result.hpp"
#include "../dump/append_log_manager.hpp"
#include "../dump/dump_processor.hpp"
#include "../dump/dump_loader.hpp"

class SearchEngine
{
public:
    SearchEngine();
    SearchEngine(DumpLoader& dump_loader);
    virtual ~SearchEngine();
    SearchResult* process_query(const Query* query);

    bool save_dump() const ;

protected:
private:
    void processing_query_begin(const Query* query);
    void processing_query_end(const Query* query);

    SearchResult* process_insert(const QueryInsert* query);
    SearchResult* process_search(const QuerySearch* query);
    SearchResult* process_create_table(const QueryCreateTable* query);

    std::vector<Table*> tables;
    Table* find_table(const std::string& table_name) const;

    AppendLogManager append_log;
};

#endif // SEARCHENGINE_H
