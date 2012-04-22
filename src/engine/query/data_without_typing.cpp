#include "data_without_typing.hpp"
#include "../../logger/logger.hpp"
#include "../types/type.hpp"

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

DataWithoutTyping::DataWithoutTyping()
{
    //ctor
}

DataWithoutTyping::~DataWithoutTyping()
{
    //dtor
}

bool DataWithoutTyping::set(const std::string& request)
{
    std::size_t i = 0;
    while(i < request.size() && request[i] != '/') i++;

    if (i == request.size()) {
        Logger::getInstance().log_error("Request should be in form <table_name>/<row definition>.\n Request: " + request);
        return false;
    }

    table_name = request.substr(0, i);

    // settings properties and their values
    std::string rest = request.substr(i+2); /*removed "/?" */
    std::vector<std::string> properties;
    boost::split(properties, rest, boost::is_any_of("&"));

    for(std::size_t i=0; i<properties.size(); i++) {
        std::vector<std::string> strs;
        boost::split(strs, properties[i], boost::is_any_of("="));
        if (strs.size() != 2) {
            Logger::getInstance().log_error("Wrong format. Row definition in your request isn't in format ?prop1=type1[&prop2=type2]*. Your request: " + request);
            return false;
        }

        property_names.push_back(strs[0]);
        values.push_back(Misc::url_decode(strs[1]));
    }

    return true;

}

std::string DataWithoutTyping::get_table_name() const
{
    return table_name;
}

std::vector<std::string> DataWithoutTyping::get_property_names() const
{
    return property_names;

}
std::string DataWithoutTyping::get_value_for_property(const std::string& property) const
{
    for(std::size_t i=0; i<property_names.size(); i++) {
        if (property_names[i] == property) {
            return values[i];
        }
    }
    return NULL;
}


bool DataWithoutTyping::is_matching_table_definition(const TableDefinition* table_definition) const
{
    if (property_names.size() != table_definition->get_property_names().size()) {
        Logger::getInstance().log_error("Error: Number of properties defined in you request doesn't match number of properties in table definition.\nTable = " + table_definition->get_table_name() + "\n");
        return false;
    }

    //TODO speed-up possible
    std::vector<std::string> props = table_definition->get_property_names();
    for(std::size_t i=0; i<props.size(); i++) {
        bool found = false;
        for(std::size_t j=0; !found && j<property_names.size(); j++) {
            if (property_names[j] == props[i]) {
                found = true;

                //checking if type is ok
                if (!table_definition->is_correct_value_for_property(props[i], values[j])) {
                    Logger::getInstance().log_error(std::string("Error: Value doesn't match property_type.\n") +
                                                    "Table=" + table_definition->get_table_name() + "\n" +
                                                    "Property=" + props[i] + "\n" +
                                                    "Value=" + values[j]);
                    return false;
                }
            }
        }

        if (!found) return false;
    }

    return true;
}

bool DataWithoutTyping::is_correct_query_search(const TableDefinition* table_definition) const
{
    for(std::size_t i = 0; i < property_names.size(); i++) {
        std::string prop = property_names[i];

        bool is_function = false;
        std::string function_name;
        if (prop[prop.size()-1] == ')') {
            unsigned int pos = find(prop.begin(), prop.end(), '(') - prop.begin();
            if (pos + 2 >= prop.size()) {
                Logger::getInstance().log_error("Error: " + prop + " contains ')' but doesn't contain '('.\n" +
                                        "Table = " + table_definition->get_table_name() + "\n");
                return false;
            }

            is_function = true;
            function_name = prop.substr(0, pos);
            prop = prop.substr(pos+1, prop.size() - 1);
        } else {
            is_function = false;
        }

        const Type* type = table_definition->get_property_type(prop);
        if (type == NULL) {
            Logger::getInstance().log_error("Error: Your request contains unknown property name: " + prop + ".\n" +
                                        "Table = " + table_definition->get_table_name() + "\n");
            return false;
        }

        if (!type->is_correct_value(values[i])) {
             Logger::getInstance().log_error("Error: Value for property: " + prop + " doesn't match it's type (" + type->get_name() + ".\n" +
                                        "Table = " + table_definition->get_table_name() + "\n");
            return false;
        }

        if (is_function && !type->is_correct_function(function_name)) {

             Logger::getInstance().log_error("Error: Type " + type->get_name() + " doesn't support function " + function_name + ".\n" +
                                        "Table = " + table_definition->get_table_name() + "\n");
            return false;
        }
    }

    return true;
}

