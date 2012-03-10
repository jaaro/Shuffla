#include "table.hpp"

Table::Table()
{
    //ctor
}

Table::~Table()
{
    //dtor
}

void Table::set_table_definition(const TableDefinition& td)
{
    table_definition = TableDefinition(td);
}

std::string Table::get_table_name() const
{
    return table_definition.get_table_name();
}

TableDefinition Table::get_table_definition() const
{
    return table_definition;
}

void Table::insert(const Row* new_row)
{
    //TODO
}
