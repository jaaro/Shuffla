#include "table_index.hpp"
#include "../kdtree/query_boundary.hpp"
#include "../kdtree/search_tasks.hpp"

#include <queue>

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
    int offset = query_params->offset;
    int limit = query_params->limit;

    std::vector<const Row*> result;

    if (limit == 0) {
        return result;
    }

    QueryBoundary query_boundary(index_info_, query_params);

    bool order_by_defined = query_params->order_by.size();
    int order_by_index;
    int order_by_boundary_index;
    bool is_desc;

    if (order_by_defined) {
        order_by_index = index_info_.get_table_definition()->get_property_index(query_params->order_by[0].first);
        order_by_boundary_index = index_info_.get_boundary_index(order_by_index);
        is_desc = (query_params->order_by[0].second == QueryParameters::DESC);
    }

    auto comp = [&](const SearchTask* lhs, const SearchTask* rhs ) -> bool {
        if (order_by_defined) {
            const Type* left = lhs->get_comparision_value(order_by_index, order_by_boundary_index, is_desc);
            const Type* right = rhs->get_comparision_value(order_by_index, order_by_boundary_index, is_desc);

            if (left == NULL) return false;
            if (right == NULL) return true;

            bool is_smaller = left->is_smaller(right);
            return !(is_smaller ^ is_desc);
        } else {
            //TODO wrong
            return false;
        }
    };

    std::priority_queue< SearchTask* , std::vector<SearchTask*>, decltype( comp ) > queue( comp );

    queue.push(new SearchTaskSearchNode(kd_tree_));

    while(!queue.empty()) {
        SearchTask* task = queue.top(); queue.pop();

        SearchTaskSearchNode* search_node = dynamic_cast<SearchTaskSearchNode*>(task);
        if (search_node != NULL) {
            std::vector<SearchTask*> result = search_node->get_vertice()->search(query_boundary);
            for(std::size_t i=0; i<result.size(); i++) {
                queue.push(result[i]);
            }
        } else {
            SearchTaskFoundRow* found_row = dynamic_cast<SearchTaskFoundRow*>(task);
            if (offset > 0) offset--;
            else {
                result.push_back(found_row->get_row());
                if (--limit == 0) {
                    return result;
                }
            }
        }
    }

    return result;
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
