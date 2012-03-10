#include "table_definition.hpp"
#include "../../logger/logger.hpp"

#include <boost/algorithm/string.hpp>
#include <algorithm>

TableDefinition::TableDefinition()
{
    //ctor
}

TableDefinition::~TableDefinition()
{
    //dtor
}

TableDefinition::TableDefinition(const TableDefinition& table_def)
{
    table_name = table_def.table_name;
    property_names = table_def.property_names;
    property_types = table_def.property_types;
}

std::string TableDefinition::get_table_name() const
{
    return table_name;
}

bool TableDefinition::create_table_from_request(const std::string& request)
{
    property_names.clear();
    property_types.clear();

    std::vector<std::string> parts;
    boost::split(parts, request, boost::is_any_of("/"));

    if (parts.size() != 4) {
        Logger::getInstance().log_error("Create table request in wrong format. Should be /create_table/<table_name>/<table_definition>\n]Your request: " + request);
        return false;
    }

    if (parts[3].size() < 3 || parts[3][0] != '?') {
        Logger::getInstance().log_error("Create table request in wrong format. Table definition is empty? Please check examples.\nYour request: " + request);
        return false;
    }

    // setting table name
    table_name = parts[2];

    // settings properties and their types
    parts[3] = parts[3].substr(1);
    std::vector<std::string> properties;
    boost::split(properties, parts[3] /* without '?' */, boost::is_any_of("&"));

    for(std::size_t i=0; i<properties.size(); i++) {
        std::vector<std::string> strs;
        boost::split(strs, properties[i], boost::is_any_of("="));
        if (strs.size() != 2) {
            Logger::getInstance().log_error("Create table request in wrong format. Table definition in your request isn't in format ?prop1=type1[&prop2=type2]*. Your request: " + request);
            return false;
        }

        if (!types.is_correct_type(strs[1])) {
          Logger::getInstance().log_error("Create table request in wrong format. Property type is wrong in at least one place. Your request: " + request);
          return false;
        }

        bool result = add_table_property(types.string_to_type(strs[1]), strs[0]);
        if (!result) {
          Logger::getInstance().log_error("Create table request in wrong format. There are more than one definition of property " + strs[0] + " Your request: " + request);
          return false;
        }
    }

    return true;
}

bool TableDefinition::add_table_property(const Types::Type& type, const std::string& name)
{
    if (find(property_names.begin(), property_names.end(), name) != property_names.end()) {
        return false;
    }

    property_types.push_back(type);
    property_names.push_back(name);

    return true;
}


std::vector<std::string> TableDefinition::get_property_names() const {
  return property_names;
}

bool TableDefinition::is_correct_value_for_property(const std::string& property, const std::string& value) const {
  for(std::size_t i=0; i<property_names.size(); i++) {
    if (property == property_names[i]) {
      if (!types.is_correct_value(property_types[i], value)) {
        //TODO log error
        return false;
      }
      return true;
    }
  }

  return false;
}
