#include <iostream>
#include <boost/lexical_cast.hpp>

#include "row.hpp"
#include "../../engine/types/type_int.hpp"
#include "../../engine/types/type_string.hpp"


Row::Row(const TableDefinition& table_definition, DumpLoader& dump_loader)
{
    std::vector<std::string> props = table_definition.get_property_names();
    for(std::size_t i=0; i<props.size(); i++) {
        int value_size = dump_loader.get_next_int();
        dump_loader.get_next_char();
        std::string value = dump_loader.get_next_chars(value_size);

        add_value(table_definition.get_property_type(props[i]), value);
    }
}

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


void Row::add_value(const Type* type, const std::string& value)
{
    if (type->get_name() == "int") {
        values.push_back(new TypeInt(value));
    } else if (type->get_name() == "string") {
        values.push_back(new TypeString(value));
    } else {
        //TODO log error

        //adding value so db is consistent
        values.push_back(new TypeString(std::string("")));
    }
}

std::string Row::to_string() const
{
    std::string result = "";
    for(std::size_t i=0; i<values.size(); i++) {
        std::string value = values[i]->to_string();
        result += boost::lexical_cast<std::string>( value.size() ) + ":" + value;
    }
    return result;
}

