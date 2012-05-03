#include "boundary.hpp"

Limiter::Limiter(const std::string& property_name, const Type* bound, bool is_upper_bound, bool is_inclusive)
    : property_name_(property_name), bound_(bound), is_upper_bound_(is_upper_bound), is_inclusive_(is_inclusive)
{ }

Limiter::~Limiter() {}

bool Limiter::is_more_strict(const Limiter& rhs) const
{
    if (is_upper_bound_ != rhs.is_upper_bound()) {
        //TODO
        std::cerr << "Fatal error 1\n";
    }

    if (bound_->equals(rhs.get_bound_value()->to_string())) {
        bool left = is_inclusive();
        bool right = rhs.is_inclusive();

        if (left == right) return false;
        return (left == false);
    }

    if (is_upper_bound_) return bound_->is_smaller(rhs.get_bound_value()->to_string());
    else return bound_->is_greater(rhs.get_bound_value()->to_string());
}

bool Limiter::is_value_matching(const Type* rhs) const
{
    if (is_upper_bound_ && is_inclusive_) return bound_->is_smaller_or_equal(rhs->to_string());
    if (is_upper_bound_ && !is_inclusive_) return bound_->is_smaller(rhs->to_string());
    if (!is_upper_bound_ && is_inclusive_) return bound_->is_greater_or_equal(rhs->to_string());
    if (!is_upper_bound_ && !is_inclusive_) return bound_->is_greater(rhs->to_string());
    assert(!"Not possible to get here");
    return false;
}

Limiter Limiter::createReverseLimiter() const
{
    return Limiter(property_name_, bound_, !is_upper_bound_, !is_inclusive_);
}

const Type* Limiter::get_bound_value() const
{
    return bound_;
}

bool Limiter::is_upper_bound() const
{
    return is_upper_bound_;
}

bool Limiter::is_inclusive() const
{
    return is_inclusive_;
}


const std::string& Limiter::get_property_name() const
{
    return property_name_;
}





Boundary::Boundary(const TableIndexInfo& table_index_info) : table_index_info_(table_index_info)
{
    //ctor
}

Boundary::~Boundary()
{
    //dtor
}



void Boundary::add_limiter(Limiter limiter)
{
    bool is_upper_bound = limiter.is_upper_bound();

    std::map<std::string, Limiter>& current = (is_upper_bound ? upper_bounds_ : lower_bounds_);
    std::map<std::string, Limiter>::iterator it = current.find(limiter.get_property_name());
    if (it == current.end() || limiter.is_more_strict(it->second)) {
        current.insert(std::pair<std::string, Limiter>(limiter.get_property_name(), limiter));
    }

}

const std::map<std::string, Limiter>& Boundary::get_upper_bounds() const {
    return upper_bounds_;
}

const std::map<std::string, Limiter>& Boundary::get_lower_bounds() const {
    return lower_bounds_;
}

bool Boundary::is_point_inside(const Row* boundary) const
{
    for(std::map<std::string, Limiter>::const_iterator it = lower_bounds_.begin(); it!=lower_bounds_.end(); it++) {
        const Limiter& limit = it->second;
        if (!limit.is_value_matching(boundary->get_value(limit.get_property_name()))) {
            return false;
        }
    }

    for(std::map<std::string, Limiter>::const_iterator it = upper_bounds_.begin(); it!=upper_bounds_.end(); it++) {
        const Limiter& limit = it->second;
        if (!limit.is_value_matching(boundary->get_value(limit.get_property_name()))) {
            return false;
        }
    }
    return true;
}

bool Boundary::contains(const Boundary& other_boundary) const
{
    for(std::map<std::string, Limiter>::const_iterator it = other_boundary.get_lower_bounds().begin(); it != other_boundary.get_lower_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        if (lower_bounds_.find(other_limit.get_property_name()) != lower_bounds_.end()) return false;
        if (other_limit.is_more_strict(lower_bounds_.find(other_limit.get_property_name())->second)) return false;
    }

    for(std::map<std::string, Limiter>::const_iterator it = other_boundary.get_upper_bounds().begin(); it != other_boundary.get_upper_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        if (upper_bounds_.find(other_limit.get_property_name()) != upper_bounds_.end()) return false;
        if (other_limit.is_more_strict(upper_bounds_.find(other_limit.get_property_name())->second)) return false;
    }

    return true;
}
