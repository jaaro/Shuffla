#ifndef QUERYDISPATCHER_H
#define QUERYDISPATCHER_H

#include <string>

class QueryDispatcher
{
  public:
    QueryDispatcher();
    virtual ~QueryDispatcher();
    std::string process_query(const std::string& request);
  protected:
  private:
};

#endif // QUERYDISPATCHER_H
