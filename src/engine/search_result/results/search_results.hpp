#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include "../search_result.hpp"
#include "../../storage/row.hpp"

class SearchResults : public SearchResult
{
public:
    SearchResults(const std::vector<const Row*> results);
    virtual ~SearchResults();

    virtual std::string to_string() const ;
protected:
    const std::vector<const Row*> results;
private:
};

#endif // SEARCHRESULTS_H
