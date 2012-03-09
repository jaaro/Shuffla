#ifndef QUERYCREATETABLE_H
#define QUERYCREATETABLE_H

#include "../query.hpp"
#include "../../table/table_definition.hpp"
#include <memory>

class QueryCreateTable : public Query
{
public:
    static const std::string HTTP_PREFIX;

    QueryCreateTable();
    virtual ~QueryCreateTable();

    virtual Query* parse(const std::string& request) const ;
    virtual bool set(const std::string& request) ;
    virtual bool is_modyfing_data() const;
protected:
private:
  TableDefinition table_definition;
};

#endif // QUERYCREATETABLE_H
