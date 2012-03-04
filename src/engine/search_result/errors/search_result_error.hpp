#ifndef SEARCHRESULTERROR_H
#define SEARCHRESULTERROR_H

#include "../search_result.hpp"

class SearchResultError : public SearchResult
{
public:
    SearchResultError(const std::string& error_message);
    virtual ~SearchResultError();
    virtual std::string to_string() const;
protected:
private:
    std::string error_message;
};

#endif // SEARCHRESULTERROR_H
