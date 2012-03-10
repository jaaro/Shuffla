#ifndef QUERY_INSERT_HPP
#define QUERY_INSERT_HPP

#include "../query.hpp"
#include "../data_without_typing.hpp"

class QueryInsert : public Query
{
public:
    static const std::string HTTP_PREFIX;

    QueryInsert();
    virtual ~QueryInsert();

    virtual bool set(const std::string& request);
    virtual Query* parse(const std::string& request) const ;
    virtual bool is_modyfing_data() const;

    DataWithoutTyping get_parsed_row() const;
    std::string get_table_name() const;
protected:
private:
    DataWithoutTyping parsed_row;
};

#endif // QUERY_INSERT_HPP
