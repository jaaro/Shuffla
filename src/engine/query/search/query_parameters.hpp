#ifndef QUERYPARAMETERS_H
#define QUERYPARAMETERS_H

#include "../../table/table_definition.hpp"
#include "../data_without_typing.hpp"
#include "functions/search_function.hpp"
#include "../../../storage/row/row.hpp"
class QueryParameters
{
public:
    QueryParameters();
    virtual ~QueryParameters();

    bool set(const TableDefinition& table, const DataWithoutTyping& data);
    bool is_matching(const Row* row) const ;
protected:
private:
    std::vector<const SearchFunction*> parameters;
    std::vector<SearchFunction*> registered_functions;

    void register_functions();
};

#endif // QUERYPARAMETERS_H
