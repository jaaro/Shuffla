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

    TypeInt(const std::string& number);
    TypeInt(const TYPE value);

    virtual Type* clone() const;

    virtual bool is_correct_value(const std::string& value) const ;
    virtual bool equals(const std::string& value) const ;
    virtual ~TypeInt();
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

#endif // TYPEINT_H
