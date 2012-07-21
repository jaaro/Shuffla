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
    virtual ~Boundary();

    virtual bool is_point_inside(const Row* boundary) const ;
    virtual bool contains(const Boundary& other_boundary) const ;
    virtual bool disjoint(const Boundary& other_boundary) const ;
    virtual bool add_limiter(Limiter limiter) ;

    virtual bool is_good_limiter(const Limiter& limiter) const ;
    virtual bool is_good_limiter_internal(const Limiter& limiter) const ;

    virtual const Type* get_lower_bound_for_property(const std::string& property_name) const ;
    virtual const Type* get_upper_bound_for_property(const std::string& property_name) const ;

    //TODO should be protected or private
    virtual const std::map<std::string, Limiter>& get_upper_bounds() const ;
    virtual const std::map<std::string, Limiter>& get_lower_bounds() const ;

    void debug() const;
protected:
    const TableIndexInfo& table_index_info_;
private:

    std::map<std::string, Limiter> upper_bounds_;
    std::map<std::string, Limiter> lower_bounds_;
};

#endif // BOUNDARY_H
