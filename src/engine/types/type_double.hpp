#ifndef TYPEDOUBLE_H
#define TYPEDOUBLE_H

#include "type_number.hpp"

class TypeDouble : public TypeNumber
{
public:
    typedef double TYPE;

    virtual std::string get_name() const
    {
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

    virtual bool is_smaller(const std::string& value) const ;
    virtual bool is_smaller_or_equal(const std::string& value) const ;
    virtual bool is_bigger(const std::string& value) const ;
    virtual bool is_bigger_or_equal(const std::string& value) const ;

protected:
private:
    const TYPE value;
};

#endif // TYPEDOUBLE_H
