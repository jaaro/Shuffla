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

    virtual ~TypeInt();
    TYPE get_value() const ;
    virtual std::string to_string() const;
protected:
private:
    const TYPE value;
};

#endif // TYPEINT_H
