#ifndef QUERYDISPATCHER_H
#define QUERYDISPATCHER_H

#include <string>


#include "../engine/query/query_create.hpp"


class QueryDispatcher
{
public:
    QueryDispatcher();
    virtual ~QueryDispatcher();
    std::string process_query(const std::string& request);
protected:
private:
    QueryCreate query_parser;
};

#endif // QUERYDISPATCHER_H
