#include "search_tasks.hpp"

SearchTaskFoundRow::SearchTaskFoundRow(const Row* row) : row_(row)
{

}
SearchTaskFoundRow::~SearchTaskFoundRow()
{

}

const Type* SearchTaskFoundRow::get_comparision_value(int property_index, int boundary_index, bool is_order_descending) const
{
    return row_->get_value(property_index);
}

const Row* SearchTaskFoundRow::get_row() const
{
    return row_;
}


SearchTaskSearchNode::SearchTaskSearchNode(KDVertice* vertice) : vertice_(vertice)
{

}

SearchTaskSearchNode::~SearchTaskSearchNode()
{

}


const Type* SearchTaskSearchNode::get_comparision_value(int property_index, int boundary_index, bool is_order_descending) const
{
    if (is_order_descending) return vertice_->get_boundary().get_upper_bound(boundary_index).get_bound_value();
    else return vertice_->get_boundary().get_lower_bound(boundary_index).get_bound_value();
}

KDVertice* SearchTaskSearchNode::get_vertice() const
{
    return vertice_;
}
