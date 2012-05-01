#include "kd_vertice.hpp"

KDVertice::KDVertice(const TableIndexInfo* table_index_info, Boundary boundary) : table_index_info_(table_index_info), boundary_(boundary)
{
    //TODO
}

KDVertice::KDVertice(const TableIndexInfo* table_index_info) : table_index_info_(table_index_info)
{
    //TODO
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
    for(std::set<const Row*>::iterator it = rows_.begin(); it!=rows_.end(); it++) {
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
    if (!boundary_.is_point_inside(table_index_info_, row)) return false;
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
    if (!boundary_.is_point_inside(table_index_info_, row)) return false;
    if (!contains_row(row)) return false;

    rows_.erase(rows_.find(row));
    if (left_ != NULL) left_->delete_row(row);
    if (right_ != NULL) right_->delete_row(row);
    return true;
}

std::vector<const Row*>  KDVertice::search(const QueryBoundary& boundary) const {
    if (boundary.contains(boundary_)) return std::vector<const Row*>(rows_.begin(), rows_.end());
    if (left_ == NULL) return linear_filter(boundary);

    std::vector<const Row*> result = left_->search(boundary);
    std::vector<const Row*> result2 = right_->search(boundary);
    result.insert(result.end(), result2.begin(), result2.end());

    return result;
}

void KDVertice::rebuild() {
    //TODO
    return ;
}
