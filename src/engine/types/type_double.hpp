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

    virtual Type* clone() const;

    virtual bool is_correct_value(const std::string& value) const ;
    virtual bool equals(const std::string& value) const ;
    virtual ~TypeDouble();
    TYPE get_value() const ;
    virtual std::string to_string() const;

    virtual bool is_smaller(const std::string& value) const ;
    virtual bool is_smaller_or_equal(const std::string& value) const ;
    virtual bool is_greater(const std::string& value) const ;
    virtual bool is_greater_or_equal(const std::string& value) const ;

protected:
private:
    const TYPE value;
};

#endif // TYPEDOUBLE_H
