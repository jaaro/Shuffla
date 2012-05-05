#include <boost/lexical_cast.hpp>
#include <cassert>

#include "type_double.hpp"

TypeDouble::TypeDouble(const TypeDouble::TYPE value) : value(value)
{
    // intensionally nothing
}

TypeDouble::TypeDouble(const std::string& number) : value (boost::lexical_cast<TypeDouble::TYPE>( number ))
{
    // intensionally nothing
}

TypeDouble::~TypeDouble()
{
    //dtor
}

Type* TypeDouble::clone() const
{
    return new TypeDouble(value);
}

TypeDouble::TYPE TypeDouble::get_value() const
{
    return value;
}


std::string TypeDouble::to_string() const
{
    return Misc::double_to_string( value );
}

bool TypeDouble::is_correct_value(const std::string& value) const
{
    return Misc::can_be_parsed_to_double(value);
}

bool TypeDouble::is_smaller(const Type* type) const
{
    const TypeDouble* v = dynamic_cast<const TypeDouble*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_double() > get_double();
}

bool TypeDouble::is_smaller_or_equal(const Type* type) const
{
    const TypeDouble* v = dynamic_cast<const TypeDouble*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_double() >= get_double();
}

bool TypeDouble::is_greater(const Type* type) const
{

    const TypeDouble* v = dynamic_cast<const TypeDouble*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_double() < get_double();
}

bool TypeDouble::is_greater_or_equal(const Type* type) const
{
    const TypeDouble* v = dynamic_cast<const TypeDouble*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_double() <= get_double();
}

bool TypeDouble::equals(const Type* type) const
{
    const TypeDouble* v = dynamic_cast<const TypeDouble*>(type);
    if (v == NULL) {
        assert(!"Comparision of different types");
    }
    return v->get_double() == get_double();
}

double TypeDouble::get_double() const {
    return value;
}
