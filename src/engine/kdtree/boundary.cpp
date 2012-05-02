#include "boundary.hpp"

Boundary::Boundary(const TableIndexInfo& table_index_info) : table_index_info_(table_index_info)
{
    //ctor
}

Boundary::~Boundary()
{
    //dtor
}


bool Boundary::is_point_inside(const Row* boundary) const {
    //TODO
    return true;
}

bool Boundary::contains(const Boundary& other_boundary) const {
    //TODO
    return true;
}
