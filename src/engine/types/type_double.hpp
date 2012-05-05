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

    explicit TypeDouble(const std::string& number);
    explicit TypeDouble(const TYPE value);

    virtual Type* clone() const;

    virtual bool is_correct_value(const std::string& value) const ;
    virtual ~TypeDouble();
    TYPE get_value() const ;
    virtual std::string to_string() const;

    virtual bool is_smaller(const Type* type) const ;
    virtual bool is_smaller_or_equal(const Type* type) const ;
    virtual bool is_greater(const Type* type) const ;
    virtual bool is_greater_or_equal(const Type* type) const ;
    virtual bool equals(const Type* type) const ;

    double get_double() const;

protected:
private:
    const TYPE value;
};

#endif // TYPEDOUBLE_H
