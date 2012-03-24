#ifndef TYPEDOUBLE_H
#define TYPEDOUBLE_H


#include "type.hpp"

class TypeDouble : public Type
{
public:
    typedef double TYPE;

    virtual std::string get_name() const {
        return "double";
    }

    TypeDouble(const std::string& number);
    TypeDouble(const TYPE value);

    virtual bool is_correct_value(const std::string& value) const ;
    virtual bool is_correct_function(const std::string& function_name) const ;
    virtual bool equals(const std::string& value) const ;
    virtual ~TypeDouble();
    TYPE get_value() const ;
    virtual std::string to_string() const;
protected:
private:
    const TYPE value;
};

#endif // TYPEDOUBLE_H
