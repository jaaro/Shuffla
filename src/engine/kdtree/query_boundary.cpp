#include "query_boundary.hpp"
#include "../types/type_int.hpp"
#include "../types/type_string.hpp"
#include "../types/type_double.hpp"

#include "../query/search/functions/search_function_equal.hpp"
#include "../query/search/functions/search_function_prefix.hpp"
#include "../query/search/functions/search_function_smaller.hpp"
#include "../query/search/functions/search_function_greater.hpp"
#include "../query/search/functions/search_function_smaller_or_equal.hpp"
#include "../query/search/functions/search_function_greater_or_equal.hpp"

QueryBoundary::QueryBoundary(const TableIndexInfo& table_index_info, boost::shared_ptr<QueryParameters> query_params) : Boundary(table_index_info), query_params_(query_params)
{
    const std::vector<SearchFunction*> params = query_params_->get_parameters();

    are_there_extra_requiremens_ = true;
    for(std::size_t i=0; i<params.size(); i++) {
        std::string property_name = params[i]->get_property_name();
        Type* value = params[i]->get_value();
        int property_index = table_index_info.get_table_definition()->get_property_index(property_name);

        if (dynamic_cast<SearchFunctionGreater*>(params[i]) != NULL) {
            add_limiter(Limiter(property_index, value, false, false));
        }

        else if (dynamic_cast<SearchFunctionGreaterOrEqual*>(params[i]) != NULL) {
            add_limiter(Limiter(property_index, value, false, true));
        } else if (dynamic_cast<SearchFunctionSmaller*>(params[i]) != NULL) {
            add_limiter(Limiter(property_index, value, true, false));
        } else if (dynamic_cast<SearchFunctionSmallerOrEqual*>(params[i]) != NULL) {
            add_limiter(Limiter(property_index, value, true, true));
        } else if (dynamic_cast<SearchFunctionEqual*>(params[i]) != NULL) {
            add_limiter(Limiter(property_index, value, true, true));
            add_limiter(Limiter(property_index, value, false, true));
        } else if (dynamic_cast<SearchFunctionPrefix*>(params[i]) != NULL) {
            add_limiter(Limiter(property_index, value, false, true));
            std::string text = value->to_string();
            text[text.size() - 1]++;
            TypeString* text_obj = new TypeString(text);
            add_limiter(Limiter(property_index, text_obj, true, false));
            delete text_obj;
        }
    }
}

boost::shared_ptr<QueryParameters> QueryBoundary::get_query_params() const
{
    return query_params_;
}

bool QueryBoundary::are_there_extra_requiremens() const
{
    return are_there_extra_requiremens_;
}
