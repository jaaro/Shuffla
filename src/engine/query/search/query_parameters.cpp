#include "query_parameters.hpp"
#include "functions/search_function_equal.hpp"
#include "functions/search_function_prefix.hpp"
#include "functions/search_function_smaller.hpp"
#include "functions/search_function_greater.hpp"
#include "functions/search_function_smaller_or_equal.hpp"
#include "functions/search_function_greater_or_equal.hpp"
#include "../../../logger/logger.hpp"

#include <boost/algorithm/string.hpp>
#include <climits>

QueryParameters::QueryParameters()
{
    offset = 0;
    limit = INT_MAX;
}

QueryParameters::~QueryParameters()
{
    for(std::size_t i=0; i<registered_functions.size(); i++) {
        delete registered_functions[i];
    }
    for(std::size_t i=0; i<parameters.size(); i++) {
        delete parameters[i];
    }
}

bool QueryParameters::set(const TableDefinition* table_definition, const DataWithoutTyping& data)
{
    parameters.clear();
    register_functions();

    std::vector<std::string> property_names = data.get_property_names();
    for(std::size_t i = 0; i < property_names.size(); i++) {
        std::string prop = property_names[i];
        std::string value = data.get_value_for_property(prop);

        if (is_special_property(prop)) {
            bool success = set_special_property(table_definition, prop, value);
            if (!success) {
                Logger::getInstance().log_error("QueryParameters: something wrong with:" + prop + "=" + value);
                return false;
            }
            continue;
        }

        SearchFunction* function = NULL;
        for(std::size_t i=0; i<registered_functions.size(); i++) {
            if (registered_functions[i]->set(prop)) {
                function = registered_functions[i]->clone();
                break;
            }
        }

        if (function == NULL) {
            Logger::getInstance().log_error("QueryParameters: Unable to understund "+prop+"\nPlease check documentation for more details about search syntax.");
            return false;
        }

        const Type* type = table_definition->get_property_type(function->get_property_name());

        if (type == NULL) {
            Logger::getInstance().log_error("QueryParameters: Table " + table_definition->get_table_name() + " doesnt have property named " + function->get_property_name());
            return false;
        }

        if (!type->is_correct_value(value)) {
            Logger::getInstance().log_error("QueryParameters: Value " + value + " doesn't match type of property " + function->get_property_name() + "(which is " + type->get_name() + ").");
            return false;
        }

        if (!function->is_available_for_type(type)) {
            Logger::getInstance().log_error("QueryParameters: Provided function " + prop + " is not available for type " + type->get_name() + ".");
            return false;
        }

        function->set_value(value);
        parameters.push_back(function);
    }

    return true;
}

bool QueryParameters::is_matching(const Row* row) const
{
    for(std::size_t i=0; i<parameters.size(); i++) {
        if (!parameters[i]->is_matching(row)) {
            return false;
        }
    }
    return true;
}

void QueryParameters::register_functions()
{
    registered_functions.clear();
    registered_functions.push_back(new SearchFunctionEqual());
    registered_functions.push_back(new SearchFunctionPrefix());
    registered_functions.push_back(new SearchFunctionSmaller());
    registered_functions.push_back(new SearchFunctionGreater());
    registered_functions.push_back(new SearchFunctionSmallerOrEqual());
    registered_functions.push_back(new SearchFunctionGreaterOrEqual());
}

bool QueryParameters::is_special_property(const std::string& name) const
{
    return name == "ORDER_BY" || name == "LIMIT" || name == "OFFSET";
}

bool QueryParameters::set_special_property(const TableDefinition* table_definition, const std::string& name, const std::string& value)
{
    if (name == "ORDER_BY") {
        std::vector<std::string> strs;
        boost::split(strs, value, boost::is_any_of(","));

        for(size_t i=0; i<strs.size(); i++) {
            if (strs[i].size() == 0) {
                Logger::getInstance().log_error("Search parameters: You forgot to provide property name in search parameters");
                return false;
            }
            QueryParameters::Order order = ASC;
            if (strs[i][0] == '-') {
                order = DESC;
                strs[i] = strs[i].substr(1);
            }

            if (!Misc::is_possible_property_name(strs[i])) {
                Logger::getInstance().log_error("Search params: Incorrect property name. It is not valid:" + strs[i]);
                return false;
            }

            if (table_definition->get_property_type(strs[i]) == NULL) {
                Logger::getInstance().log_error("Search params: Property name doesn't match table definition. Table name: "+ table_definition->get_table_name() + "\nProperty name: " + strs[i]);
                return false;
            }
            order_by.push_back(std::make_pair(strs[i], order));
        }
    } else if (name == "LIMIT") {
        try {
            limit = Misc::string_to_int(value);
        } catch(std::exception e) {
            Logger::getInstance().log_error("Search parameters: LIMIT is not an int. You gave limit = " + value);
            return false;
        }
        return true;
    } else if (name == "OFFSET") {
        try {
            offset = Misc::string_to_int(value);
        } catch(std::exception e) {
            Logger::getInstance().log_error("Search parameters: OFFSET is not an int. You gave offset = " + value);
            return false;
        }
        return true;
    } else {
        Logger::getInstance().log_error("Developer error in QueryParameters. Please contact author of this software.");
        return false;
    }
    return true;
}
