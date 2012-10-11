#ifndef LIMITER_H
#define LIMITER_H

#include "../table_index/table_index_info.hpp"
#include "../storage/row.hpp"

class Pivot
{
public:
    Pivot(int property_index, const Type* value, bool is_max, bool is_inclusive);
    Pivot& operator=(const Pivot& pivot);
    Pivot(const Pivot& pivot);
    Pivot();

    virtual ~Pivot();

    bool is_more_strict(const Pivot& rhs) const ;
    bool is_value_matching(const Type* value) const ;
    bool is_value_matching(const Row* value) const ;
    bool is_disjoint(const Pivot& rhs) const ;

    bool is_upper_bound() const ;
    bool is_inclusive() const ;
    const Type* get_bound_value() const ;
    int get_property_index() const ;

    Pivot createReversePivot() const ;
    void debug() const;

    bool is_unbounded() const ;
private:

    int property_index_;
    Type* bound_;

    bool is_upper_bound_;
    bool is_inclusive_;
};


#endif // LIMITER_H
