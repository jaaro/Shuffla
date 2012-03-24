#ifndef SEARCHFUNCTIONSMALLER_H
#define SEARCHFUNCTIONSMALLER_H

#include "search_function_with_prefix.hpp"

class SearchFunctionSmaller : public SearchFunctionWithPrefix
{
public:
    SearchFunctionSmaller();
    virtual ~SearchFunctionSmaller();

    virtual bool is_matching(const Row* row) const;
    bool is_correct_prefix(const std::string& prefix) const;
    virtual bool is_available_for_type(const Type* type) const;
    virtual SearchFunction* clone() const ;

protected:
private:
    std::string property_name;
    std::string value;
protected:
private:
};

#endif // SEARCHFUNCTIONSMALLER_H
