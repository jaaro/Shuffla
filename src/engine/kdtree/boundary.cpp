#include "boundary.hpp"

Limiter::Limiter(const std::string& property_name, const Type* bound, bool is_upper_bound, bool is_inclusive)
    : property_name_(property_name), bound_(bound->clone()), is_upper_bound_(is_upper_bound), is_inclusive_(is_inclusive)
{ }

Limiter::~Limiter() {}

bool Limiter::is_more_strict(const Limiter& rhs) const
{
    if (is_upper_bound_ != rhs.is_upper_bound()) {
        //TODO
        std::cerr << "Fatal error 1\n";
        assert(!"WTF");
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
    if (!is_upper_bound_ && is_inclusive_) return bound_->is_smaller_or_equal(rhs->to_string());
    if (!is_upper_bound_ && !is_inclusive_) return bound_->is_smaller(rhs->to_string());
    if (is_upper_bound_ && is_inclusive_) return bound_->is_greater_or_equal(rhs->to_string());
    if (is_upper_bound_ && !is_inclusive_) return bound_->is_greater(rhs->to_string());
    assert(!"Not possible to get here");
    return false;
}

bool Limiter::is_disjoint(const Limiter& rhs) const
{
    if (rhs.is_upper_bound() == is_upper_bound()) return false;

    if (bound_->equals(rhs.get_bound_value()->to_string())) {
        return !rhs.is_inclusive() || !is_inclusive();
    }

    if (is_upper_bound()) return bound_->is_smaller(rhs.get_bound_value()->to_string());
    else return bound_->is_greater(rhs.get_bound_value()->to_string());
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

void Limiter::debug() const
{
    std::cerr << "LIMITER " << property_name_;
    std::cerr << (is_upper_bound() ? "<" : ">");
    std::cerr << (is_inclusive() ? "=" : "");
    std::cerr << get_bound_value()->to_string() << "\n";
}




Boundary::Boundary(const TableIndexInfo& table_index_info) : table_index_info_(table_index_info)
{
    //ctor
}

Boundary::~Boundary()
{
    //dtor
}



bool Boundary::add_limiter(Limiter limiter)
{
    bool is_upper_bound = limiter.is_upper_bound();

    std::map<std::string, Limiter>& current = (is_upper_bound ? upper_bounds_ : lower_bounds_);
    std::map<std::string, Limiter>::iterator it = current.find(limiter.get_property_name());
    if (it == current.end() || limiter.is_more_strict(it->second)) {
        if (it != current.end()) current.erase(it);
        current.insert(std::pair<std::string, Limiter>(limiter.get_property_name(), limiter));
        return true;
    }
    return false;
}

bool Boundary::is_good_limiter(const Limiter& limiter) const
{
    return is_good_limiter_internal(limiter) && is_good_limiter_internal(limiter.createReverseLimiter());
}

bool Boundary::is_good_limiter_internal(const Limiter& limiter) const
{
    bool is_upper_bound = limiter.is_upper_bound();

    const std::map<std::string, Limiter>& current = (is_upper_bound ? upper_bounds_ : lower_bounds_);
    std::map<std::string, Limiter>::const_iterator it = current.find(limiter.get_property_name());
    return (it == current.end() || limiter.is_more_strict(it->second));
}

const std::map<std::string, Limiter>& Boundary::get_upper_bounds() const
{
    return upper_bounds_;
}

const std::map<std::string, Limiter>& Boundary::get_lower_bounds() const
{
    return lower_bounds_;
}

bool Boundary::is_point_inside(const Row* point) const
{
    for(std::map<std::string, Limiter>::const_iterator it = lower_bounds_.begin(); it!=lower_bounds_.end(); it++) {
        const Limiter& limit = it->second;
        if (!limit.is_value_matching(point->get_value(limit.get_property_name()))) {
            return false;
        }
    }

    for(std::map<std::string, Limiter>::const_iterator it = upper_bounds_.begin(); it!=upper_bounds_.end(); it++) {
        const Limiter& limit = it->second;
        if (!limit.is_value_matching(point->get_value(limit.get_property_name()))) {
            return false;
        }
    }
    return true;
}

bool Boundary::contains(const Boundary& other_boundary) const
{
    for(std::map<std::string, Limiter>::const_iterator it = other_boundary.get_lower_bounds().begin(); it != other_boundary.get_lower_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        if (lower_bounds_.find(other_limit.get_property_name()) == lower_bounds_.end()) continue;
        if (lower_bounds_.find(other_limit.get_property_name())->second.is_more_strict(other_limit)) return false;
    }

    for(std::map<std::string, Limiter>::const_iterator it = other_boundary.get_upper_bounds().begin(); it != other_boundary.get_upper_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        if (upper_bounds_.find(other_limit.get_property_name()) == upper_bounds_.end()) continue;
        if (upper_bounds_.find(other_limit.get_property_name())->second.is_more_strict(other_limit)) return false;
    }

    for(std::map<std::string, Limiter>::const_iterator it = get_lower_bounds().begin(); it != get_lower_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        if (other_boundary.get_lower_bounds().find(other_limit.get_property_name()) ==  other_boundary.get_lower_bounds().end()) return false;
    }

    for(std::map<std::string, Limiter>::const_iterator it = get_upper_bounds().begin(); it != get_upper_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        if (other_boundary.get_upper_bounds().find(other_limit.get_property_name()) ==  other_boundary.get_upper_bounds().end()) return false;
    }

    return true;
}

bool Boundary::disjoint(const Boundary& other_boundary) const
{
    for(std::map<std::string, Limiter>::const_iterator it = other_boundary.get_lower_bounds().begin(); it != other_boundary.get_lower_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        if (upper_bounds_.find(other_limit.get_property_name()) == upper_bounds_.end()) continue;
        if (upper_bounds_.find(other_limit.get_property_name())->second.is_disjoint(other_limit)) return true;
    }

    for(std::map<std::string, Limiter>::const_iterator it = other_boundary.get_upper_bounds().begin(); it != other_boundary.get_upper_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        if (lower_bounds_.find(other_limit.get_property_name()) == lower_bounds_.end()) continue;
        if (lower_bounds_.find(other_limit.get_property_name())->second.is_disjoint(other_limit)) return true;
    }

    return false;
}

void Boundary::debug() const
{
    std::cerr << "==== BOUNDARY ====\n";
    for(std::map<std::string, Limiter>::const_iterator it = get_lower_bounds().begin(); it != get_lower_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        other_limit.debug();
    }

    for(std::map<std::string, Limiter>::const_iterator it = get_upper_bounds().begin(); it != get_upper_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        other_limit.debug();
    }
}
