#include "type_int.hpp"

#include <cassert>

TypeInt::TypeInt(const TypeInt::TYPE value) : value(value)
{
    // intensionally nothing
}

TypeInt::TypeInt(const std::string& number) : value (Misc::string_to_int( number ))
{
    // intensionally nothing
}

TypeInt::~TypeInt()
{
    //dtor
}


TypeInt::TYPE TypeInt::get_value() const
{
    return value;
}

Type* TypeInt::clone() const
{
    return new TypeInt(value);
}

std::string TypeInt::to_string() const
{
    return Misc::int_to_string( value );
}

bool TypeInt::is_correct_value(const std::string& value) const
{
    return Misc::can_be_parsed_to_int(value);
}

bool TypeInt::is_smaller(const Type* type) const
{
    const TypeInt* v = dynamic_cast<const TypeInt*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_int() > get_int();
}

bool TypeInt::is_smaller_or_equal(const Type* type) const
{
    const TypeInt* v = dynamic_cast<const TypeInt*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_int() >= get_int();
}

bool TypeInt::is_greater(const Type* type) const
{
    const TypeInt* v = dynamic_cast<const TypeInt*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_int() < get_int();
}

bool TypeInt::is_greater_or_equal(const Type* type) const
{
    const TypeInt* v = dynamic_cast<const TypeInt*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_int() <= get_int();
}

bool TypeInt::equals(const Type* type) const
{
    const TypeInt* v = dynamic_cast<const TypeInt*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_int() == get_int();
}

int TypeInt::get_int() const {
    return value;
}
