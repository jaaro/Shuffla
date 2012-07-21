#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <string>

/**
 * Base class for communication between engine and rest of the world.
 * It recives "some results" and should be able to print it in readable form by functiom to_string().
 */
class SearchResult
{
public:
    SearchResult();
    virtual ~SearchResult();
    virtual std::string to_string() const = 0;
    virtual int get_status_code() const = 0;
protected:
private:
};

#endif // SEARCHRESULT_H
