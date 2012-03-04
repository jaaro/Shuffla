#ifndef QUERYCREATETABLE_H
#define QUERYCREATETABLE_H

#include "../query.hpp"

class QueryCreateTable : public Query
{
public:
    static const std::string HTTP_PREFIX;

    QueryCreateTable();
    QueryCreateTable(const std::string& request);
    virtual ~QueryCreateTable();

    virtual Query* parse(const std::string& request) const ;
    virtual bool is_modyfing_data() const;
protected:
private:
};

#endif // QUERYCREATETABLE_H
