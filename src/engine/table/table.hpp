#ifndef TABLE_H
#define TABLE_H

#include "table_definition.hpp"
#include "../../storage/row/row.hpp"
#include "../../dump/dump_processor.hpp"

class Table
{
public:
    Table();
    virtual ~Table();

    void set_table_definition(const TableDefinition& table_definition);
    TableDefinition get_table_definition() const ;
    std::string get_table_name() const ;

    void insert(const Row* row);
    void dump_table(DumpProcessor& dump_processor) const;
protected:
private:
    TableDefinition table_definition;
    std::vector<const Row*> rows;
};

#endif // TABLE_H
