#include <boost/algorithm/string/predicate.hpp>

#include "query_insert.hpp"

QueryInsert::QueryInsert()
{
  //ctor
}

QueryInsert::QueryInsert(const std::string& request)
{
  //ctor
}

QueryInsert::~QueryInsert()
{
  //dtor
}

Query* QueryInsert::parse(const std::string& request) const {
  if (boost::starts_with(request, "/insert")) {
    return new QueryInsert(request);
  }

  return NULL;
}


bool QueryInsert::is_modyfing_data() const {
  return true;
}
