#include "search_tasks.hpp"

SearchTaskFoundRow::SearchTaskFoundRow(const Row* row) : row_(row)
{

}
SearchTaskFoundRow::~SearchTaskFoundRow()
{

}

const Type* SearchTaskFoundRow::get_comparison_value(int property_index, int boundary_index, bool is_order_descending) const
{
    return row_->get_value(property_index);
}

const Row* SearchTaskFoundRow::get_row() const
{
    return row_;
}


SearchTaskSearchNode::SearchTaskSearchNode(KDVertex* vertex) : vertex_(vertex)
{

}

SearchTaskSearchNode::~SearchTaskSearchNode()
{

}


const Type* SearchTaskSearchNode::get_comparison_value(int property_index, int boundary_index, bool is_order_descending) const
{
    if (is_order_descending) return vertex_->get_boundary().get_upper_bound(boundary_index).get_bound_value();
    else return vertex_->get_boundary().get_lower_bound(boundary_index).get_bound_value();
}

KDVertex* SearchTaskSearchNode::get_vertex() const
{
    return vertex_;
}
