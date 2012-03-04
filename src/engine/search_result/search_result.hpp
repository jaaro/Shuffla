#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <string>

class SearchResult
{
public:
    SearchResult();
    virtual ~SearchResult();
    virtual std::string to_string() const = 0;
protected:
private:
};

#endif // SEARCHRESULT_H
