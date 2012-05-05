#include "boundary.hpp"

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
