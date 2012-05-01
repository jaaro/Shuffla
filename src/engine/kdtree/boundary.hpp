#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "../table_index/table_index_info.hpp"
#include "../storage/row.hpp"

class Boundary
{
    public:
        Boundary();
        virtual ~Boundary();

        virtual bool is_point_inside(const TableIndexInfo* table_index_info, const Row* boundary) const ;
    protected:
    private:
};

#endif // BOUNDARY_H
