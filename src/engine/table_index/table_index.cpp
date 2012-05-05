#include "table_index.hpp"
#include "../kdtree/query_boundary.hpp"

TableIndex::TableIndex(TableIndexInfo index_info) : index_info_(index_info)
{
    kd_tree_ = new KDVertice(index_info_);
}

TableIndex::~TableIndex()
{
    delete kd_tree_;
}

std::vector<const Row*> TableIndex::search(boost::shared_ptr<QueryParameters> query_params) const
{
    QueryBoundary query_boundary(index_info_, query_params);
    return kd_tree_->search(query_boundary);
}

void TableIndex::delete_row(const Row* row)
{
    kd_tree_->delete_row(row);
}

void TableIndex::insert_row(const Row* row)
{
    kd_tree_->insert_row(row, 0);
}

void TableIndex::bulk_build(std::vector<const Row*> rows)
{
    kd_tree_->clear();
    kd_tree_->add_collection(rows);
}

void TableIndex::dump_all_rows(DumpSaver& dump_saver) const
{
    kd_tree_->dump_all_rows(dump_saver);
}

const TableIndexInfo& TableIndex::get_index_info() const
{
    return index_info_;
}
