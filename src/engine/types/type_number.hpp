#ifndef TYPENUMBER_H
#define TYPENUMBER_H

#include "type.hpp"

class TypeNumber : public Type
{
public:
    TypeNumber();
    virtual ~TypeNumber();

    virtual bool is_smaller(const std::string& value) const = 0;
    virtual bool is_smaller_or_equal(const std::string& value) const = 0;
    virtual bool is_greater(const std::string& value) const = 0;
    virtual bool is_greater_or_equal(const std::string& value) const = 0;
protected:
private:
};

#endif // TYPENUMBER_H
