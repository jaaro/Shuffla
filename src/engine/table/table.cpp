#include "table.hpp"
#include "../search_result/results/search_results.hpp"

#include "../kdtree/query_boundary.hpp"

#include <boost/lexical_cast.hpp>

Table::Table()
{
    //ctor
}

Table::Table(DumpLoader& dump_loader)
{
    table_definition = new TableDefinition(dump_loader);
    std::vector<const Row*> rows;
    std::string line = dump_loader.get_line();
    int size = Misc::string_to_int(line);
    while(size--) {
        rows.push_back(new Row(table_definition, dump_loader));
    }
    dump_loader.get_line();
    TableIndexInfo index_info(table_definition, table_definition->get_property_names());
    indexes.push_back(new TableIndex(index_info));
    indexes[0]->bulk_build(rows);
}

Table::~Table()
{
    for(std::size_t i=0; i<indexes.size(); i++) {
        delete indexes[i];
    }

    delete table_definition;
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
    for(std::size_t index = 0; index<indexes.size(); index++) {
        indexes[index]->insert_row(new_row);
    }
}


void Table::dump_table(DumpSaver& dump_saver) const
{
    dump_saver.append(table_definition->to_string());
    indexes[0]->dump_all_rows(dump_saver);
}

SearchResult* Table::search(boost::shared_ptr<QueryParameters> params) const
{
    QueryBoundary boundary(params);
    //TODO count != 777 ;)
    return new SearchResults(params, indexes[0]->search(params), 777);
}


int Table::remove(boost::shared_ptr<QueryParameters> params)
{
    QueryBoundary boundary(params);
    std::vector<const Row*> results = indexes[0]->search(params);

    for(std::size_t index = 0; index<indexes.size(); index++) {
        for(std::size_t i=0; i<results.size(); i++) {
            indexes[index]->delete_row(results[i]);
        }
    }

    for(std::size_t j=0; j<results.size(); j++) {
        delete results[j];
    }

    return results.size();
}
