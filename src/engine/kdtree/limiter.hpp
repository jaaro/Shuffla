#ifndef LIMITER_H
#define LIMITER_H

#include "../table_index/table_index_info.hpp"
#include "../storage/row.hpp"

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

    std::string property_name_;
    Type* bound_;

    bool is_upper_bound_;
    bool is_inclusive_;
};


#endif // LIMITER_H
