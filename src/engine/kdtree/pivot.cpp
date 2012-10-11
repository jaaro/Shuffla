#include "pivot.hpp"

Pivot::Pivot(int property_index, const Type* bound, bool is_upper_bound, bool is_inclusive)
    : property_index_(property_index),
    bound_(bound != NULL ? bound->clone() : NULL),
    is_upper_bound_(is_upper_bound),
    is_inclusive_(is_inclusive)
{ }

Pivot::Pivot(const Pivot& pivot) {
    property_index_ = pivot.property_index_;
    bound_ = (pivot.bound_ != NULL ? pivot.bound_->clone() : NULL);
    is_upper_bound_ = pivot.is_upper_bound_;
    is_inclusive_ = pivot.is_inclusive_;
} 

Pivot::Pivot() : property_index_(-1), bound_(NULL), is_upper_bound_(false), is_inclusive_(false) {}

Pivot::~Pivot() {
    delete bound_;
}

Pivot& Pivot::operator=(const Pivot& pivot){
    property_index_ = pivot.property_index_;
    bound_ = (pivot.bound_ != NULL ? pivot.bound_->clone() : NULL);
    is_upper_bound_ = pivot.is_upper_bound_;
    is_inclusive_ = pivot.is_inclusive_;
    return *this;
} 

bool Pivot::is_more_strict(const Pivot& rhs) const
{
    if (is_upper_bound_ != rhs.is_upper_bound()) {
        assert(!"Pivot::is_more_strict error. Please report this as a bug. Stacktrace will be very appreciated.");
    }

    if (bound_->equals(rhs.get_bound_value())) {
        bool left = is_inclusive();
        bool right = rhs.is_inclusive();

        if (left == right) return false;
        return (left == false);
    }

    if (is_upper_bound_) return bound_->is_smaller(rhs.get_bound_value());
    else return bound_->is_greater(rhs.get_bound_value());
}

bool Pivot::is_value_matching(const Type* rhs) const
{
    if (!is_upper_bound_ && is_inclusive_) return bound_->is_smaller_or_equal(rhs);
    if (!is_upper_bound_ && !is_inclusive_) return bound_->is_smaller(rhs);
    if (is_upper_bound_ && is_inclusive_) return bound_->is_greater_or_equal(rhs);
    if (is_upper_bound_ && !is_inclusive_) return bound_->is_greater(rhs);
    assert(!"Not possible to get here");
    return false;
}


bool Pivot::is_value_matching(const Row* value) const
{
    const Type* type =  value->get_value(property_index_);
    return is_value_matching(type);
}

bool Pivot::is_disjoint(const Pivot& rhs) const
{
    if (rhs.is_upper_bound() == is_upper_bound()) return false;

    if (bound_->equals(rhs.get_bound_value())) {
        return !rhs.is_inclusive() || !is_inclusive();
    }

    if (is_upper_bound()) return bound_->is_smaller(rhs.get_bound_value());
    else return bound_->is_greater(rhs.get_bound_value());
}

Pivot Pivot::createReversePivot() const
{
    return Pivot(property_index_, bound_, !is_upper_bound_, !is_inclusive_);
}

const Type* Pivot::get_bound_value() const
{
    return bound_;
}

bool Pivot::is_upper_bound() const
{
    return is_upper_bound_;
}

bool Pivot::is_inclusive() const
{
    return is_inclusive_;
}


int Pivot::get_property_index() const
{
    return property_index_;
}

void Pivot::debug() const
{
    std::cerr << "LIMITER " << property_index_;
    std::cerr << (is_upper_bound() ? "<" : ">");
    std::cerr << (is_inclusive() ? "=" : "");
    std::cerr << get_bound_value()->to_string() << "\n";
}


    bool Pivot::is_unbounded() const {
    return bound_ == NULL;
    }
