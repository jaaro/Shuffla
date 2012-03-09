#include "table_definition.hpp"

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

std::string TableDefinition::get_table_name() const
{
    return table_name;
}

bool TableDefinition::create_table_from_request(const std::string& request)
{
    property_name.clear();
    property_type.clear();

    std::vector<std::string> parts;
    boost::split(parts, request, boost::is_any_of("/"));

    if (parts.size() != 4) {
        //should be [empty string, insert, table_name, table_definition]
        return false;
    }

    if (parts[3].size() < 3 || parts[3][0] != '?') {
        //table definition should be in form ?name=type&name2=type2 etc
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
        boost::split(strs, request, boost::is_any_of("="));
        if (strs.size() != 2) {
            //format for single entry should be value = type
            return false;
        }

        bool result = add_table_property(string_to_type(strs[0]), strs[1]);
        if (!result) {
          // property name exist more than once in request
          return false;
        }
    }

    return true;
}

TableDefinition::Type TableDefinition::string_to_type(const std::string& type) const
{
    if (type == "int" || type == "integer" || type == "long") {
        return Type::Integer;
    } else {
        return Type::String;
    }
}

bool TableDefinition::add_table_property(const Type& type, const std::string& name)
{
    if (find(property_name.begin(), property_name.end(), name) != property_name.end()) {
        return false;
    }

    property_type.push_back(type);
    property_name.push_back(name);

    return true;
}
