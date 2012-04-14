#ifndef TABLE_H
#define TABLE_H

#include "table_definition.hpp"
#include "../storage/row.hpp"
#include "../../dump/dump_saver.hpp"
#include "../../dump/dump_loader.hpp"
#include "../search_result/search_result.hpp"
#include "../query/search/query_parameters.hpp"

class Table
{
public:
    Table();
    Table(DumpLoader& dump_loader);
    virtual ~Table();

    void set_table_definition(const TableDefinition* table_definition);
    TableDefinition* get_table_definition() const ;
    std::string get_table_name() const ;

    int delete_all(const QueryParameters& params);
    void insert(const Row* row);

    SearchResult* search(const QueryParameters& params) const ;
    void dump_table(DumpSaver& dump_processor) const;
protected:
private:
    TableDefinition* table_definition;
    std::vector<const Row*> rows;
};

#endif // TABLE_H
