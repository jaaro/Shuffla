#include "search_results.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>

SearchResults::SearchResults(boost::shared_ptr<QueryParameters> params, const std::vector<const Row*>& results, int count): params(params), results(results), count(count)
{
    //ctor
}

SearchResults::~SearchResults()
{
    //dtor
}


std::string SearchResults::to_string() const
{
    boost::property_tree::ptree root;
    //root.put<int>("overall_count", count );
    root.put<int>("offset", params->offset);
    root.put<int>("limit", params->limit);

    if (params->order_by.size() > 0) {
        root.put<std::string>("order_by",
                              (params->order_by[0].second == QueryParameters::ASC ? "" : "-") +
                              params->order_by[0].first
                             );
    }

    boost::property_tree::ptree results_array;
    for(std::size_t i=0; i<results.size(); i++) {
        results_array.push_back(std::make_pair("", results[i]->get_property_tree()));
    }

    root.put_child("results", results_array);

    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, root);

    return ss.str();
}

int SearchResults::get_status_code() const
{
    return 200;
}
