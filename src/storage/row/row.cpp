#include <iostream>

#include "row.hpp"
#include "../../engine/types/type_int.hpp"
#include "../../engine/types/type_string.hpp"

Row::Row(const TableDefinition& table_definition, const DataWithoutTyping& data) : table_definition(&table_definition)
{
  std::vector<std::string> props = table_definition.get_property_names();
  for(std::size_t i=0; i<props.size(); i++) {
    add_value(table_definition.get_property_type(props[i]), data.get_value_for_property(props[i]));
  }
}

Row::~Row()
{
  //dtor
}


void Row::add_value(const Types::Type& type, const std::string& value) {
  switch(type) {
    case Types::Int:
      values.push_back(new TypeInt(value));
      break;
    case Types::String:
      values.push_back(new TypeString(value));
      break;
    default:
      //TODO log error

      //adding value so db is consistent
      values.push_back(new TypeString(std::string("")));

  }
}
