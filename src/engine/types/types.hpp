#ifndef TYPES_H
#define TYPES_H

#include <string>

#include "type.hpp"

class Types
{
public:
    Types();
    virtual ~Types();

    Type* string_to_type(const std::string& type) const;
    bool is_correct_type(const std::string& type) const;
    bool is_correct_value(const Type* type, const std::string& value) const ;

protected:
private:
};

#endif // TYPES_H
