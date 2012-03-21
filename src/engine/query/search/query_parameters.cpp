#include "query_parameters.hpp"
#include "functions/search_function_equal.hpp"
#include "functions/search_function_prefix.hpp"
#include "../../../logger/logger.hpp"

QueryParameters::QueryParameters()
{
    //ctor
}

QueryParameters::~QueryParameters()
{
    //dtor
}

bool QueryParameters::set(const TableDefinition& table_definition, const DataWithoutTyping& data)
{
    parameters.clear();
    register_functions();

    std::vector<std::string> property_names = data.get_property_names();
    for(std::size_t i = 0; i < property_names.size(); i++) {
        std::string prop = property_names[i];
        std::string value = data.get_value_for_property(prop);

        SearchFunction* function = NULL;
        for(std::size_t i=0; i<registered_functions.size(); i++) {
            if (registered_functions[i]->set(prop)) {
                function = registered_functions[i]->clone();
                break;
            }
        }

        if (function == NULL) {
            Logger::getInstance().log_error("Unable to understund "+prop+"\nPlease check documentation for more details about search syntax.");
            return false;
        }

        const Type* type = table_definition.get_property_type(function->get_property_name());

        if (type == NULL) {
            Logger::getInstance().log_error("Table " + table_definition.get_table_name() + " doesnt not have property named " + function->get_property_name());
            return false;
        }

        if (!type->is_correct_value(value)) {
            //TODO log error
            return false;
        }

        if (!function->is_available_for_type(type)) {
            //TODO log error
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
}
