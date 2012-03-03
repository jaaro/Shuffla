#ifndef QUERY_INSERT_HPP
#define QUERY_INSERT_HPP

#include "../query.hpp"


class QueryInsert : public Query
{
  public:
    QueryInsert();
    QueryInsert(const std::string& request);
    virtual ~QueryInsert();
    virtual Query* parse(const std::string& request) const ;
    virtual bool is_modyfing_data() const;
  protected:
  private:
};

#endif // QUERY_INSERT_HPP
