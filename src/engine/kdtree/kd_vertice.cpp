#include "kd_vertice.hpp"

KDVertice::KDVertice(const TableIndexInfo& table_index_info, Boundary boundary) : table_index_info_(table_index_info), boundary_(boundary)
{
    left_ = NULL;
    right_ = NULL;
}

KDVertice::KDVertice(const TableIndexInfo& table_index_info) : table_index_info_(table_index_info), boundary_(Boundary(table_index_info))
{
    left_ = NULL;
    right_ = NULL;
}

KDVertice::~KDVertice()
{
    delete left_;
    delete right_;
}


void KDVertice::clear() {
    rows_.clear();
    delete left_;
    delete right_;
}

void KDVertice::dump_all_rows(DumpSaver& dump_saver) const {
    dump_saver.append(Misc::int_to_string(rows_.size()) + "\n");
    for(std::multiset<const Row*>::iterator it = rows_.begin(); it!=rows_.end(); it++) {
        dump_saver.append((*it)->to_string());
    }
}

void KDVertice::add_collection(std::vector<const Row*> rows) {
    //TODO possible optimization
    for(std::size_t i=0; i<rows.size(); i++) {
        rows_.insert(rows[i]);
    }

    rebuild();
}

bool KDVertice::contains_row(const Row* row) const {
    return rows_.find(row) != rows_.end();
}


bool KDVertice::insert_row(const Row* row) {
    if (!boundary_.is_point_inside(row)) return false;
    if (contains_row(row)) return false;
    rows_.insert(row);

    if (left_ == NULL && rows_.size() > 3) {
        rebuild();
        return true;
    }

    if (left_ != NULL) left_->insert_row(row);
    if (right_ != NULL) right_->insert_row(row);


    return true;
}

bool KDVertice::delete_row(const Row* row) {
    if (!boundary_.is_point_inside(row)) return false;
    if (!contains_row(row)) return false;

    rows_.erase(rows_.find(row));
    if (left_ != NULL) left_->delete_row(row);
    if (right_ != NULL) right_->delete_row(row);
    return true;
}

std::vector<const Row*>  KDVertice::search(const QueryBoundary& query_boundary) const {
    if (query_boundary.contains(boundary_)) return filter_non_index_conditions(query_boundary);
    if (left_ == NULL) return linear_filter(query_boundary);

    std::vector<const Row*> result = left_->search(query_boundary);
    std::vector<const Row*> result2 = right_->search(query_boundary);
    result.insert(result.end(), result2.begin(), result2.end());

    return result;
}

void KDVertice::rebuild() {
    //TODO
    return ;
}


std::vector<const Row*>  KDVertice::linear_filter(const QueryBoundary& query_boundary) const {
    std::vector<const Row*> rows;

    for(std::multiset<const Row*>::iterator it = rows_.begin(); it!=rows_.end(); it++) {
        if (query_boundary.get_query_params()->is_matching(*it)) {
            rows.push_back(*it);
        }
    }

    return rows;
}

std::vector<const Row*>  KDVertice::filter_non_index_conditions(const QueryBoundary& query_boundary) const {
    //TODO I am filtering ALL conditions
    std::vector<const Row*> rows;

    for(std::multiset<const Row*>::iterator it = rows_.begin(); it!=rows_.end(); it++) {
        if (query_boundary.get_query_params()->is_matching(*it)) {
            rows.push_back(*it);
        }
    }

    return rows;
}
