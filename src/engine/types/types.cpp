#include <boost/lexical_cast.hpp>

#include "types.hpp"

Types::Types()
{
  //ctor
}

Types::~Types()
{
  //dtor
}


bool Types::is_correct_type(const std::string& type) const {
  if (type == "int" || type == "integer" || type == "long") {
        return true;
    } if (type == "string" || type =="varchar" || type == "text") {
        return true;
    }
    return false;
}

Types::Type Types::string_to_type(const std::string& type) const
{
    if (type == "int" || type == "integer" || type == "long") {
        return Type::Integer;
    }
    return Type::String;
}


bool Types::is_correct_value(const Type& type, const std::string& value) const {
  switch(type) {
    case String: return true;
    case Integer:
      try
      {
        boost::lexical_cast<Types::INTEGER>( value );
        return true;
      }
      catch( const boost::bad_lexical_cast & )
      {
        return false;
      }
    default:
      //TODO log error
      return false;
  }
}
