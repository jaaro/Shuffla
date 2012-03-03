#include <boost/algorithm/string/predicate.hpp>

#include "query_search.hpp"

QuerySearch::QuerySearch()
{
  //ctor
}

QuerySearch::QuerySearch(const std::string& request)
{
  //ctor
}

QuerySearch::~QuerySearch()
{
  //dtor
}


Query* QuerySearch::parse(const std::string& request) const {
  if (boost::starts_with(request, "/search")) {
    return new QuerySearch(request);
  }

  return NULL;
}

bool QuerySearch::is_modyfing_data() const {
  return false;
}
