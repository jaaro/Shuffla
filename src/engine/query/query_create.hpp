#ifndef QUERYCREATE_H
#define QUERYCREATE_H

#include <vector>

#include "query.hpp"

class QueryCreate
{
public:
    QueryCreate();
    virtual ~QueryCreate();
    void register_handler(Query* handler);
    Query* parse_query(const std::string& request) const ;
protected:
private:
    std::vector<Query*> handlers_list;
};

#endif // QUERYCREATE_H
