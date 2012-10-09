#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "../table_index/table_index_info.hpp"
#include "../storage/row.hpp"
#include "pivot.hpp"

#include <map>

class Boundary
{
public:
    Boundary(const TableIndexInfo& table_index_info);
    Boundary(const Boundary& boundary);

    virtual bool is_point_inside(const Row* boundary) const ;
    virtual bool contains(const Boundary& other_boundary) const ;
    virtual bool disjoint(const Boundary& other_boundary) const ;
    virtual bool add_pivot(Pivot pivot) ;

    virtual bool is_good_pivot(const Pivot& pivot) const ;
    virtual bool is_good_pivot_internal(const Pivot& pivot) const ;

    virtual const Pivot& get_upper_bound(int index) const ;
    virtual const Pivot& get_lower_bound(int index) const ;

    void debug() const;

protected:
    const TableIndexInfo& table_index_info_;
private:
    std::vector<Pivot> upper_bounds_;
    std::vector<Pivot> lower_bounds_;
    int size_;
};

#endif // BOUNDARY_H
