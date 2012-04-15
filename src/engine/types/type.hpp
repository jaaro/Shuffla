#ifndef TYPE_H
#define TYPE_H

#include <string>

#include "../../misc/misc.hpp"

/**
 * In shuffla there are few possible types:
 * 1) int
 * 2) double
 * 3) string
 *
 * Representation of every type inherits from this class.
 */
class Type
{
public:
    Type();
    virtual ~Type();
    virtual std::string get_name() const = 0;
    virtual std::string to_string() const = 0;
    virtual bool is_correct_value(const std::string& value) const = 0;
    virtual bool is_correct_function(const std::string& function_name) const = 0;
    virtual bool equals(const std::string& value) const = 0;
protected:
private:
};

#endif // TYPE_H
