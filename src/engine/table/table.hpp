#ifndef TABLE_H
#define TABLE_H

#include "table_definition.hpp"
#include "../storage/row.hpp"
#include "../../dump/dump_saver.hpp"
#include "../../dump/dump_loader.hpp"
#include "../search_result/search_result.hpp"
#include "../query/search/query_parameters.hpp"
#include "../table_index/table_index.hpp"

class Table
{
public:
    Table();
    Table(DumpLoader& dump_loader);
    virtual ~Table();

    // table definition
    void set_table_definition(const TableDefinition* table_definition);
    TableDefinition* get_table_definition() const ;
    std::string get_table_name() const ;

    // insert, search, remove
    void insert(const Row* row);
    int remove(boost::shared_ptr<QueryParameters> params);
    SearchResult* search(boost::shared_ptr<QueryParameters> params) const ;

    void dump_table(DumpSaver& dump_processor) const;
protected:
private:
    TableDefinition* table_definition;
    std::vector<TableIndex*> indexes;
};

#endif // TABLE_H
