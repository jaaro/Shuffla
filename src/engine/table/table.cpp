#include "table.hpp"
#include "../search_result/results/search_results.hpp"

#include <boost/lexical_cast.hpp>

Table::Table()
{
    //ctor
}

Table::Table(DumpLoader& dump_loader)
{
    table_definition = new TableDefinition(dump_loader);

    std::string line = dump_loader.get_line();
    int size = Misc::string_to_int(line);
    while(size--) {
        rows.push_back(new Row(table_definition, dump_loader));
    }
    dump_loader.get_line();
}

Table::~Table()
{
    //dtor
}

void Table::set_table_definition(const TableDefinition* td)
{
    table_definition = new TableDefinition(td);
}

std::string Table::get_table_name() const
{
    return table_definition->get_table_name();
}

TableDefinition* Table::get_table_definition() const
{
    return table_definition;
}

void Table::insert(const Row* new_row)
{
    rows.push_back(new_row);
}


void Table::dump_table(DumpSaver& dump_saver) const
{
    dump_saver.append(table_definition->to_string());
    dump_saver.append(Misc::int_to_string( rows.size() ) + "\n");
    for(std::size_t i=0; i<rows.size(); i++) {
        dump_saver.append(rows[i]->to_string());
    }
}

SearchResult* Table::search(const QueryParameters& params) const
{
    std::vector<const Row*> results;
    for(std::size_t i=0; i<rows.size(); i++) {

        if (params.is_matching(rows[i])) {
            results.push_back(rows[i]);
        }
    }

    return new SearchResults(results);
}


int Table::remove(const QueryParameters& params)
{
    std::vector<const Row*> results;
    for(std::size_t i=0; i<rows.size(); i++) {

        if (params.is_matching(rows[i])) {
            results.push_back(rows[i]);
        }
    }
    return results.size();
}
