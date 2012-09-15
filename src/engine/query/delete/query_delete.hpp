#ifndef QUERYDELETE_H
#define QUERYDELETE_H

#include "../query.hpp"
#include "../data_without_typing.hpp"

class QueryDelete : public Query
{
public:
    static const std::string HTTP_PREFIX;

    QueryDelete();
    virtual ~QueryDelete();

    virtual bool set(const std::string& request);
    virtual Query* parse(const std::string& request) const ;
    virtual bool is_modifying_data() const;
    DataWithoutTyping get_parsed_query() const;
    std::string get_table_name() const;
protected:
private:
    DataWithoutTyping parsed_query;
};

#endif // QUERYDELETE_H
