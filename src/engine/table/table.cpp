#include "table.hpp"

#include <boost/lexical_cast.hpp>

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
    rows.push_back(new_row);
}


void Table::dump_table(DumpProcessor& dump_processor) const
{
    dump_processor.append(table_definition.to_string());
    dump_processor.append("ELEMENTS " + boost::lexical_cast<std::string>( rows.size() ));
    for(std::size_t i=0; i<rows.size(); i++) {
        dump_processor.append(rows[i]->to_string());
    }
}
