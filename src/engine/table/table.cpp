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
    //random_shuffle(rows.begin(), rows.end());
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

    if (params.order_by.size() > 0 ) {
        std::string order_by = params.order_by[0].first;
        bool ascending = (params.order_by[0].second == QueryParameters::ASC);

        auto comp = [&](const Row* a, const Row* b)-> bool {
            bool res = a->get_value(order_by)->is_greater(b->get_value(order_by)->to_string());
            if (ascending) res = !res;
            return res;
        };

        sort(results.begin(), results.end(), comp);
    }

    int count = results.size();
    int start = std::min(count, params.offset);
    int end = (int)std::min((long long)count, (long long)params.offset + params.limit);
    std::vector<const Row*> sliced_results(results.begin() + start, results.begin() + end);

    return new SearchResults(params, sliced_results, count);
}


int Table::remove(const QueryParameters& params) {
    std::vector<const Row*> results;
    for(std::size_t i=0; i<rows.size(); i++) {

        if (params.is_matching(rows[i])) {
            results.push_back(rows[i]);
        }
    }

    for(std::size_t j=0; j<results.size(); j++) {
        for(std::size_t i=0; i<rows.size(); i++) {
            if (rows[i] == results[j]) {
                rows.erase(rows.begin() + i);
                delete results[j];
                break;
            }
        }
    }

    return results.size();
}
