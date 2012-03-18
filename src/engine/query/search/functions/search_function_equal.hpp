#ifndef SEARCHFUNCTIONEQUAL_H
#define SEARCHFUNCTIONEQUAL_H

#include "search_function.hpp"

class SearchFunctionEqual : public SearchFunction
{
public:
    SearchFunctionEqual();
    SearchFunctionEqual(const SearchFunctionEqual& fun);
    virtual ~SearchFunctionEqual();

    virtual bool set(const std::string& name);
    virtual bool is_available_for_type(const Type* type) const;
    virtual SearchFunction* clone() const ;

protected:
private:
};

#endif // SEARCHFUNCTIONEQUAL_H
