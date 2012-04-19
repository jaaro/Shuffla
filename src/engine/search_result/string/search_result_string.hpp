#ifndef SEARCHRESULTSTRING_H
#define SEARCHRESULTSTRING_H

#include "../search_result.hpp"

class SearchResultString : public SearchResult
{
public:
    SearchResultString(const std::string& text);
    virtual ~SearchResultString();
    virtual std::string to_string() const;
    virtual int get_status_code() const;
protected:
private:
    std::string text;
};

#endif // SEARCHRESULTSTRING_H
