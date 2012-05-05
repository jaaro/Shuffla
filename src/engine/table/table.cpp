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

    int number_of_indexes = Misc::string_to_int(dump_loader.get_line());
    while(number_of_indexes --> 0) {
        TableIndexInfo index_info(table_definition, dump_loader);
        indexes.push_back(new TableIndex(index_info));
    }

    std::vector<const Row*> rows;
    int size = dump_loader.get_next_int();
    while(size--) {
        rows.push_back(new Row(table_definition, dump_loader));
    }
    dump_loader.get_line();

    for(std::size_t i=0; i<indexes.size(); i++) {
        indexes[i]->bulk_build(rows);
    }
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

    //work around, todo
    TableIndexInfo index_info(table_definition, table_definition->get_property_names(), std::vector<std::string>());
    indexes.push_back(new TableIndex(index_info));
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
    dump_saver.append(Misc::int_to_string(indexes.size()) + "\n");

    for(std::size_t i=0; i<indexes.size(); i++) {
        dump_saver.append(indexes[i]->get_index_info().to_string());
    }
    indexes[0]->dump_all_rows(dump_saver);
}

SearchResult* Table::search(boost::shared_ptr<QueryParameters> params) const
{
    std::vector<const Row*> results = indexes[0]->search(params);

    if (params->order_by.size() > 0 ) {
        std::string order_by = params->order_by[0].first;
        bool ascending = (params->order_by[0].second == QueryParameters::ASC);

        auto comp = [&](const Row* a, const Row* b)-> bool {
            bool res = a->get_value(order_by)->is_greater(b->get_value(order_by));
            if (ascending) res = !res;
            return res;
        };

        sort(results.begin(), results.end(), comp);
    }

    int count = results.size();
    int start = std::min(count, params->offset);
    int end = (int)std::min((long long)count, (long long)params->offset + params->limit);
    std::vector<const Row*> sliced_results(results.begin() + start, results.begin() + end);

    return new SearchResults(params, sliced_results, count);
}


int Table::remove(boost::shared_ptr<QueryParameters> params)
{
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
