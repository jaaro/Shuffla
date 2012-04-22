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

    TypeString(const TYPE value);
    virtual ~TypeString();

    virtual Type* clone() const;

    virtual bool is_correct_value(const std::string& value) const ;
    virtual bool is_correct_function(const std::string& function_name) const ;

    virtual bool is_smaller(const std::string& value) const ;
    virtual bool is_smaller_or_equal(const std::string& value) const ;
    virtual bool is_greater(const std::string& value) const ;
    virtual bool is_greater_or_equal(const std::string& value) const ;

    bool is_prefix(const std::string& prefix) const ;
    virtual bool equals(const std::string& value) const ;
    virtual std::string to_string() const;
    TYPE get_value() const ;
protected:
private:
    char* value_;
};

#endif // TYPESTRING_H
