#ifndef SEARCHFUNCTION_H
#define SEARCHFUNCTION_H

#include "../../../types/type.hpp"

class SearchFunction
{
public:
    SearchFunction();
    virtual ~SearchFunction();

    virtual bool set(const std::string& name) = 0;
    virtual bool set_value(const std::string& value) = 0;
    virtual std::string get_property_name() const = 0;
    virtual bool is_available_for_type(const Type* type) const = 0;
    virtual SearchFunction* clone() const = 0;
protected:
private:
};

#endif // SEARCHFUNCTION_H
