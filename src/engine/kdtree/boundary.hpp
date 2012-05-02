#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "../table_index/table_index_info.hpp"
#include "../storage/row.hpp"

class Boundary
{
    public:
        Boundary(const TableIndexInfo& table_index_info);
        virtual ~Boundary();

        virtual bool is_point_inside(const Row* boundary) const ;
        virtual bool contains(const Boundary& other_boundary) const ;
    protected:
    private:
        const TableIndexInfo& table_index_info_;
};

#endif // BOUNDARY_H
