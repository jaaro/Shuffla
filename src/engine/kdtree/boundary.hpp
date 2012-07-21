#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "../table_index/table_index_info.hpp"
#include "../storage/row.hpp"
#include "limiter.hpp"

#include <map>

class Boundary
{
public:
    Boundary(const TableIndexInfo& table_index_info);
    Boundary(const Boundary& boundary);

    virtual ~Boundary();

    virtual bool is_point_inside(const Row* boundary) const ;
    virtual bool contains(const Boundary& other_boundary) const ;
    virtual bool disjoint(const Boundary& other_boundary) const ;
    virtual bool add_limiter(Limiter limiter) ;

    virtual bool is_good_limiter(const Limiter& limiter) const ;
    virtual bool is_good_limiter_internal(const Limiter& limiter) const ;

    virtual const Limiter& get_upper_bound(int index) const ;
    virtual const Limiter& get_lower_bound(int index) const ;

    void debug() const;

protected:
    const TableIndexInfo& table_index_info_;
private:
    Limiter* upper_bounds_;
    Limiter* lower_bounds_;
    int size_;
};

#endif // BOUNDARY_H
