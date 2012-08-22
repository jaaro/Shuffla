#ifndef TYPESTRING_H
#define TYPESTRING_H

#include <string>

#include "type.hpp"

class TypeString : public Type
{
public:
    typedef std::string TYPE;

    virtual std::string get_name() const {
        return "string";
    }

    explicit TypeString(const TYPE value);
    virtual ~TypeString();

    virtual Type* clone() const;

    virtual bool is_correct_value(const std::string& value) const ;

    virtual bool is_smaller(const Type* type) const ;
    virtual bool is_smaller_or_equal(const Type* type) const ;
    virtual bool is_greater(const Type* type) const ;
    virtual bool is_greater_or_equal(const Type* type) const ;
    virtual bool equals(const Type* type) const ;

    bool is_prefix(const char* prefix) const ;
    bool is_substring(const char* pattern) const ;
    virtual std::string to_string() const;
    TYPE get_value() const ;

    const char* c_str() const ;
protected:
private:
    char* value_;
};

#endif // TYPESTRING_H
