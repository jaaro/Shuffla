#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include "../search_result.hpp"
#include "../../storage/row.hpp"
#include "../../query/search/query_parameters.hpp"

class SearchResults : public SearchResult
{
public:
    SearchResults(const QueryParameters& query_params, const std::vector<const Row*>& results, int count);
    virtual ~SearchResults();

    virtual std::string to_string() const ;
protected:
    std::vector<const Row*> results;
    QueryParameters params;

    int count;
private:
};

#endif // SEARCHRESULTS_H
