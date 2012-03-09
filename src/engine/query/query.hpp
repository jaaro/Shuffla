#ifndef QUERY_H
#define QUERY_H

#include <string>

class Query
{
public:
    Query();
    virtual ~Query();

    virtual bool set(const std::string& request);
    virtual Query* parse(const std::string& request) const = 0;
    virtual bool is_modyfing_data() const = 0;

    std::string to_string() const;
protected:

    std::string request;
private:
};

#endif // QUERY_H
