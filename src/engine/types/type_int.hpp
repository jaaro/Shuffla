#ifndef TYPEINT_H
#define TYPEINT_H

#include "type.hpp"

class TypeInt : public Type
{
public:
    typedef int TYPE;

    virtual std::string get_name() const {
        return "int";
    }

    explicit TypeInt(const std::string& number);
    explicit TypeInt(const TYPE value);

    virtual Type* clone() const;

    virtual bool is_correct_value(const std::string& value) const ;
    virtual ~TypeInt();
    TYPE get_value() const ;
    virtual std::string to_string() const;

    virtual bool is_smaller(const Type* type) const ;
    virtual bool is_smaller_or_equal(const Type* type) const ;
    virtual bool is_greater(const Type* type) const ;
    virtual bool is_greater_or_equal(const Type* type) const ;
    virtual bool equals(const Type* type) const ;

    int get_int() const ;
protected:
private:
    const TYPE value;
};

#endif // TYPEINT_H
