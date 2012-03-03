#ifndef QUERYSEARCH_H
#define QUERYSEARCH_H

#include "../query.hpp"

class QuerySearch : public Query
{
  public:
    QuerySearch();
    QuerySearch(const std::string& request);
    virtual ~QuerySearch();
    virtual Query* parse(const std::string& request) const ;
    virtual bool is_modyfing_data() const;
  protected:
  private:
};

#endif // QUERYSEARCH_H
