#ifndef QUERY_H
#define QUERY_H

#include <string>

class Query
{
  public:
    Query();
    virtual ~Query();

    virtual Query* parse(const std::string& request) const = 0;
    virtual bool is_modyfing_data() const = 0;
  protected:
  private:
};

#endif // QUERY_H
