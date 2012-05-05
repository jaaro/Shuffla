#include "search_tasks.hpp"

SearchTaskFoundRow::SearchTaskFoundRow(const Row* row) : row_(row)
{

}
SearchTaskFoundRow::~SearchTaskFoundRow()
{

}

const Type* SearchTaskFoundRow::get_comparision_value(const std::string& property_name, bool is_order_descending) const
{
    return row_->get_value(property_name);
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


const Type* SearchTaskSearchNode::get_comparision_value(const std::string& property_name, bool is_order_descending) const
{
    if (is_order_descending) return vertice_->get_boundary().get_upper_bound_for_property(property_name);
    else return vertice_->get_boundary().get_lower_bound_for_property(property_name);
}

KDVertice* SearchTaskSearchNode::get_vertice() const
{
    return vertice_;
}
