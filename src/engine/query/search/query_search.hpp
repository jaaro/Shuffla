#ifndef QUERYSEARCH_H
#define QUERYSEARCH_H

#include "../query.hpp"
#include "../data_without_typing.hpp"

class QuerySearch : public Query
{
public:
    static const std::string HTTP_PREFIX;

    QuerySearch();
    virtual ~QuerySearch();

    virtual bool set(const std::string& request);
    virtual Query* parse(const std::string& request) const ;
    virtual bool is_modyfing_data() const;
    DataWithoutTyping get_parsed_query() const;
protected:
private:
    DataWithoutTyping parsed_query;
};

#endif // QUERYSEARCH_H
