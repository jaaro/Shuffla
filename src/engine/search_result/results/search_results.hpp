#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include "../search_result.hpp"
#include "../../storage/row.hpp"
#include "../../query/search/query_parameters.hpp"

class SearchResults : public SearchResult
{
public:
    SearchResults(boost::shared_ptr<QueryParameters> query_params, const std::vector<const Row*>& results, int count);
    virtual ~SearchResults();

    virtual std::string to_string() const ;
    virtual int get_status_code() const;
protected:

    boost::shared_ptr<QueryParameters> params;
    std::vector<const Row*> results;

    int count;
private:
};

#endif // SEARCHRESULTS_H
