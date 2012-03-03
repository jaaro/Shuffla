#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include "query/query.hpp"

class SearchEngine
{
public:
    SearchEngine();
    virtual ~SearchEngine();
    std::string process(const Query& query);
protected:
private:
};

#endif // SEARCHENGINE_H
