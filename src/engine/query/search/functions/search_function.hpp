#ifndef SEARCHFUNCTION_H
#define SEARCHFUNCTION_H

#include "../../../types/type.hpp"

class SearchFunction
{
public:
    SearchFunction();
    virtual ~SearchFunction();


    virtual bool set_value(const std::string& value);
    virtual bool set_property_name(const std::string& value);
    virtual std::string get_property_name() const;

    virtual bool set(const std::string& name) = 0;
    virtual bool is_available_for_type(const Type* type) const = 0;
    virtual SearchFunction* clone() const = 0;
protected:
  std::string value;
  std::string property_name;
private:
};

#endif // SEARCHFUNCTION_H
