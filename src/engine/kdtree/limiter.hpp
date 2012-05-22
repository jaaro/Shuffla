#ifndef LIMITER_H
#define LIMITER_H

#include "../table_index/table_index_info.hpp"
#include "../storage/row.hpp"

class Limiter
{
public:
    Limiter(int property_index, const Type* value, bool is_max, bool is_inclusive);
    Limiter();

    virtual ~Limiter();

    bool is_more_strict(const Limiter& rhs) const ;
    bool is_value_matching(const Type* value) const ;
    bool is_disjoint(const Limiter& rhs) const ;

    bool is_upper_bound() const ;
    bool is_inclusive() const ;
    const Type* get_bound_value() const ;
    int get_property_index() const ;

    Limiter createReverseLimiter() const ;
    void debug() const;

    bool is_unbounded() const ;
private:

    int property_index_;
    Type* bound_;

    bool is_upper_bound_;
    bool is_inclusive_;
};


#endif // LIMITER_H
