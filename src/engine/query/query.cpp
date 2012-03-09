#include "query.hpp"

Query::Query()
{
    //ctor
}

Query::~Query()
{
    //dtor
}

bool Query::set(const std::string& req) {
  request = req;
  return true;
}

std::string Query::to_string() const {
  return request;
}
