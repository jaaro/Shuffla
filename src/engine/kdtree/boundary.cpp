#include "boundary.hpp"

Boundary::Boundary(const TableIndexInfo& table_index_info) : table_index_info_(table_index_info)
{
    size_ = table_index_info.get_property_index_limit();
    lower_bounds_ = std::vector<Limiter>(size_, Limiter());
    upper_bounds_ = std::vector<Limiter>(size_, Limiter());
}

Boundary::Boundary(const Boundary& boundary) :
    table_index_info_ (boundary.table_index_info_)
{
    size_ = boundary.size_;
    lower_bounds_ = boundary.lower_bounds_;
    upper_bounds_ = boundary.upper_bounds_;
}

bool Boundary::add_limiter(Limiter limiter)
{
    bool is_upper_bound = limiter.is_upper_bound();
    int property_index = limiter.get_property_index();
    int boundary_index = table_index_info_.get_boundary_index(property_index);

    std::vector<Limiter>& current = (is_upper_bound ? upper_bounds_ : lower_bounds_);
    Limiter& it = current[boundary_index];
    if (it.is_unbounded() || limiter.is_more_strict(it)) {
        current[boundary_index] = limiter;
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
    int property_index = limiter.get_property_index();
    int boundary_index = table_index_info_.get_boundary_index(property_index);

    const std::vector<Limiter>& current = (is_upper_bound ? upper_bounds_ : lower_bounds_);
    const Limiter& it = current[boundary_index];
    return (it.is_unbounded() || limiter.is_more_strict(it));
}

bool Boundary::is_point_inside(const Row* point) const
{
    for(int i=0; i<size_; i++) {
        const Limiter& limit = lower_bounds_[i];
        if (limit.is_unbounded()) continue;

        if (!limit.is_value_matching(point->get_value(limit.get_property_index()))) {
            return false;
        }
    }

    for(int i=0; i<size_; i++) {
        const Limiter& limit = upper_bounds_[i];
        if (limit.is_unbounded()) continue;

        if (!limit.is_value_matching(point->get_value(limit.get_property_index()))) {
            return false;
        }
    }

    return true;
}


bool Boundary::contains(const Boundary& other_boundary) const
{
    for(int i=0; i<size_; i++) {
        const Limiter& other_limit = other_boundary.get_lower_bound(i);
        if (other_limit.is_unbounded()) continue;

        if (lower_bounds_[i].is_unbounded()) continue;
        if (lower_bounds_[i].is_more_strict(other_limit)) return false;
    }

    for(int i=0; i<size_; i++) {
        const Limiter& other_limit = other_boundary.get_upper_bound(i);
        if (other_limit.is_unbounded()) continue;

        if (upper_bounds_[i].is_unbounded()) continue;
        if (upper_bounds_[i].is_more_strict(other_limit)) return false;
    }

    for(int i=0; i<size_; i++) {
        const Limiter& limit = lower_bounds_[i];
        if (limit.is_unbounded()) continue;

        if (other_boundary.get_lower_bound(i).is_unbounded()) return false;
    }

    for(int i=0; i<size_; i++) {
        const Limiter& limit = upper_bounds_[i];
        if (limit.is_unbounded()) continue;

        if (other_boundary.get_upper_bound(i).is_unbounded()) return false;
    }

    return true;
}

bool Boundary::disjoint(const Boundary& other_boundary) const
{
    for(int i=0; i<size_; i++) {
        const Limiter& other_limit = other_boundary.get_lower_bound(i);
        if (other_limit.is_unbounded()) continue;

        if (upper_bounds_[i].is_unbounded()) continue;
        if (upper_bounds_[i].is_disjoint(other_limit)) return true;
    }

    for(int i=0; i<size_; i++) {
        const Limiter& other_limit = other_boundary.get_upper_bound(i);

        if (lower_bounds_[i].is_unbounded()) continue;
        if (lower_bounds_[i].is_disjoint(other_limit)) return true;
    }

    return false;
}

void Boundary::debug() const
{
    /*std::cerr << "==== BOUNDARY ====\n";
    for(std::map<std::string, Limiter>::const_iterator it = get_lower_bounds().begin(); it != get_lower_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        other_limit.debug();
    }

    for(std::map<std::string, Limiter>::const_iterator it = get_upper_bounds().begin(); it != get_upper_bounds().end(); it++) {
        const Limiter& other_limit = it->second;
        other_limit.debug();
    }*/
}


const Limiter& Boundary::get_upper_bound(int index) const
{
    return upper_bounds_[index];
}

const Limiter& Boundary::get_lower_bound(int index) const
{
    return lower_bounds_[index];
}

