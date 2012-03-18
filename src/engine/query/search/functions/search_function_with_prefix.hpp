#ifndef SEARCH_FUNCTION_WITH_PREFIX_HPP
#define SEARCH_FUNCTION_WITH_PREFIX_HPP

#include "search_function.hpp"

class SearchFunctionWithPrefix : public SearchFunction
{
public:
    SearchFunctionWithPrefix();
    virtual ~SearchFunctionWithPrefix();

    virtual bool set(const std::string& name);
protected:
    virtual bool is_correct_prefix(const std::string& prefix) const = 0;
private:
};

#endif // SEARCH_FUNCTION_WITH_PREFIX_HPP
