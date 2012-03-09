#ifndef QUERYSEARCH_H
#define QUERYSEARCH_H

#include "../query.hpp"

class QuerySearch : public Query
{
public:
    static const std::string HTTP_PREFIX;

    QuerySearch();
    virtual ~QuerySearch();

    virtual bool set(const std::string& request);
    virtual Query* parse(const std::string& request) const ;
    virtual bool is_modyfing_data() const;
protected:
private:
};

#endif // QUERYSEARCH_H
