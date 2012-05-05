#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "../table_index/table_index_info.hpp"
#include "../storage/row.hpp"

#include <map>

class Limiter
{
public:
    Limiter(const std::string& property_name, const Type* value, bool is_max, bool is_inclusive);

    virtual ~Limiter();

    bool is_more_strict(const Limiter& rhs) const ;
    bool is_value_matching(const Type* value) const ;
    bool is_disjoint(const Limiter& rhs) const ;

    bool is_upper_bound() const ;
    bool is_inclusive() const ;
    const Type* get_bound_value() const ;
    const std::string& get_property_name() const ;

    Limiter createReverseLimiter() const ;
    void debug() const;

private:

    const std::string property_name_;
    const Type* bound_;

    const bool is_upper_bound_;
    const bool is_inclusive_;
};

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
