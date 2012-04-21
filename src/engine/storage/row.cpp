#include <iostream>
#include <boost/lexical_cast.hpp>

#include "row.hpp"
#include "../types/type_int.hpp"
#include "../types/type_double.hpp"
#include "../types/type_string.hpp"


Row::Row(const TableDefinition* table_definition, DumpLoader& dump_loader) : table_definition(table_definition)
{
    std::vector<std::string> props = table_definition->get_property_names();
    for(std::size_t i=0; i<props.size(); i++) {
        int value_size = dump_loader.get_next_int();
        dump_loader.get_next_char();
        std::string value = dump_loader.get_next_chars(value_size);

        // TODO BEFORE RELEASE: url_decode isn't the best way to escape characters
        add_value(table_definition->get_property_type(props[i]), Misc::url_decode(value));
    }
}

Row::Row(const TableDefinition* table_definition, const DataWithoutTyping& data) : table_definition(table_definition)
{
    std::vector<std::string> props = table_definition->get_property_names();
    for(std::size_t i=0; i<props.size(); i++) {
        add_value(table_definition->get_property_type(props[i]), data.get_value_for_property(props[i]));
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
    } else if (type->get_name() == "double") {
        values.push_back(new TypeDouble(value));
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
        // TODO BEFORE RELEASE: url_decode isn't the best way to escape characters
        std::string value = Misc::url_encode(values[i]->to_string());
        result += Misc::int_to_string( value.size() ) + ":" + value;
    }
    return result;
}

boost::property_tree::ptree Row::get_property_tree() const
{
    boost::property_tree::ptree root;
    std::vector<std::string> props = table_definition->get_property_names();
    for(std::size_t i=0; i<props.size(); i++) {
        root.put<std::string>(props[i], values[i]->to_string());
    }

    return root;
}

Type* Row::get_value (const std::string& name) const
{
    std::vector<std::string> property_names = table_definition->get_property_names();
    for(std::size_t i=0; i<property_names.size(); i++) {
        if (property_names[i] == name) return values[i];
    }

    return NULL;
}


