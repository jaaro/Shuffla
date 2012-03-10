#ifndef TYPESTRING_H
#define TYPESTRING_H

#include <string>

#include "type.hpp"

class TypeString : public Type
{
  public:
    typedef std::string TYPE;

    virtual std::string get_name() const { return "string"; }

    TypeString(const TYPE value);
    virtual ~TypeString();

    TYPE get_value() const ;
  protected:
  private:
    TYPE value;
};

#endif // TYPESTRING_H
