#include "query_parameters.hpp"
#include "functions/search_function_equal.hpp"

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
            //TODO log error
            return false;
        }

        const Type* type = table_definition.get_property_type(function->get_property_name());
        if (type == NULL) {
            //TODO log error
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

void QueryParameters::register_functions()
{
    registered_functions.clear();
    registered_functions.push_back(new SearchFunctionEqual());
}
