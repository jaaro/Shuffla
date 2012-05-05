#ifndef SEARCHFUNCTION_H
#define SEARCHFUNCTION_H


#include "../../../types/type_int.hpp"
#include "../../../types/type_string.hpp"
#include "../../../types/type_double.hpp"

#include "../../../storage/row.hpp"
#include "../../../../misc/misc.hpp"

class SearchFunction
{
public:
    SearchFunction();
    virtual ~SearchFunction();

    virtual bool set_value(const Type* type, const std::string& value);
    virtual bool set_property_name(const std::string& value);
    virtual std::string get_property_name() const;
    virtual Type* get_value() const;

    virtual bool is_matching(const Row* row) const = 0;
    virtual bool set(const std::string& name) = 0;
    virtual bool is_available_for_type(const Type* type) const = 0;
    virtual SearchFunction* clone() const = 0;

protected:
    Type* value;
    std::string property_name;
private:
};

#endif // SEARCHFUNCTION_H
