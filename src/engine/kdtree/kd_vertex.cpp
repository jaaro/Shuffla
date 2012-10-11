#include "kd_vertex.hpp"
#include "../../logger/logger.hpp"

KDVertex::KDVertex(const TableIndexInfo& table_index_info, Boundary boundary) : table_index_info_(table_index_info), boundary_(boundary)
{
    left_ = NULL;
    right_ = NULL;
    count = 0;
}

KDVertex::KDVertex(const TableIndexInfo& table_index_info) : table_index_info_(table_index_info), boundary_(Boundary(table_index_info))
{
    left_ = NULL;
    right_ = NULL;
    count = 0;
}

KDVertex::~KDVertex()
{
    delete left_;
    delete right_;
}


void KDVertex::clear()
{
    rows_.clear();
    delete left_;
    delete right_;
}

void KDVertex::dump_all_rows(DumpSaver& dump_saver) const
{
    dump_saver.append(Misc::int_to_string(rows_.size()) + "\n");
    for(auto it = rows_.begin(); it!=rows_.end(); it++) {
        dump_saver.append((*it)->to_string());
    }
}

void KDVertex::add_collection(std::vector<const Row*> rows)
{
    count += rows.size();
    rows_.insert(rows_.end(), rows.begin(), rows.end());
    for(size_t i=0; i<rows.size(); i++) {
        boundary_.expand_by_point(rows[i]);
    }
    rebuild_if_necessary();
}

int KDVertex::get_count() const {
    return count;
}

bool KDVertex::insert_row(const Row* row, int k)
{
    boundary_.expand_by_point(row);

    count++;
    if (left_ == NULL) {
        rows_.push_back(row);
        rebuild_if_necessary();
        return true;
    }

    if (pivot_.is_value_matching(row)) left_->insert_row(row, k+1);
    else right_->insert_row(row, k+1);

    rebuild_if_necessary();

    return true;
}

bool KDVertex::delete_row(const Row* row)
{
    count--;
    if (left_ == NULL) {
        for(size_t i=0; i<rows_.size(); i++) {
            if (rows_[i] == row) {
                rows_.erase(rows_.begin() + i);
            }
        }
        return true;
    }

    if (pivot_.is_value_matching(row)) left_->delete_row(row);
    else right_->delete_row(row);

    rebuild_if_necessary();
    return true;
}

std::vector<SearchTask*>  KDVertex::search(const QueryBoundary& query_boundary) const
{
    if (query_boundary.disjoint(boundary_)) {
        return std::vector<SearchTask*>();
    }

    if (left_ == NULL) {
        std::vector<const Row*> rows = linear_filter(query_boundary);

        std::vector<SearchTask*> res;
        for(std::size_t i=0; i<rows.size(); i++) res.push_back(new SearchTaskFoundRow(rows[i]));
        return res;
    }

    std::vector<SearchTask*> result;
    result.push_back(new SearchTaskSearchNode(left_));
    result.push_back(new SearchTaskSearchNode(right_));

    return result;
}

void KDVertex::collect_rows(std::vector<const Row*>& rows) {
    rows.insert(rows.end(), rows_.begin(), rows_.end());
    rows_.clear();
    if (left_ != NULL) {
        left_->collect_rows(rows);
        right_->collect_rows(rows);
    }
}

void KDVertex::rebuild_if_necessary()
{
    bool should_rebuild = false;
    if (rows_.size() > 82 && left_ == NULL)  should_rebuild = true;
    if (left_ != NULL) {
        int l = left_->get_count();
        int r = right_->get_count();
        if (l > 2*r || r > 2*l) should_rebuild = true;
    }

    if (should_rebuild) {
        if (left_ != NULL) {
            left_->collect_rows(rows_);
            right_->collect_rows(rows_);
            delete left_;
            delete right_;
        }

        pivot_ = find_good_pivot();

        Boundary left_boundary(table_index_info_);
        Boundary right_boundary(table_index_info_);

        left_ = new KDVertex(table_index_info_, left_boundary);
        right_ = new KDVertex(table_index_info_, right_boundary);
        std::vector<const Row*> left_collection, right_collection;

        for(auto it = rows_.begin(); it !=rows_.end(); it++) {
            if (pivot_.is_value_matching(*it)) {
                left_collection.push_back(*it);
            } else {
                right_collection.push_back(*it);
            }
        }

        left_->add_collection(left_collection);
        right_->add_collection(right_collection);

        rows_ = std::vector<const Row*>();
    }

}

Pivot KDVertex::find_good_pivot() const
{
    std::vector<std::string> props = table_index_info_.get_table_definition()->get_property_names();

    Pivot current;
    
    for(auto it = rows_.begin(); it !=rows_.end(); it++) {
        for(int property_index = 0; property_index < props.size(); property_index++) {
            std::string property = props[property_index];

            Pivot current(property_index, (*it)->get_value(property), rand()&1, rand()&1);
            int local_res = calculate_pivot_efficiency(current);
            if (local_res <= signed(rows_.size()) / 8) {
                return current;
            }
        }
    }

    Logger::getInstance().log_error("Unable to find good pivot");
    assert(!current.is_unbounded());

    return current;
}

int KDVertex::calculate_pivot_efficiency(const Pivot& limit) const
{
    int res = 0;
    int property_index = limit.get_property_index();

    for(auto it = rows_.begin(); it !=rows_.end(); it++) {
        if (limit.is_value_matching((*it)->get_value(property_index))) {
            res++;
        } else {
            res--;
        }
    }

    return abs(res);
}

std::vector<const Row*>  KDVertex::linear_filter(const QueryBoundary& query_boundary) const
{
    std::vector<const Row*> rows;

    for(auto it = rows_.begin(); it!=rows_.end(); it++) {
        if (query_boundary.get_query_params()->is_matching(*it)) {
            rows.push_back(*it);
        }
    }

    return rows;
}

std::vector<const Row*>  KDVertex::filter_non_index_conditions(const QueryBoundary& query_boundary) const
{
    //TODO I am filtering ALL conditions
    std::vector<const Row*> rows;

    for(auto it = rows_.begin(); it!=rows_.end(); it++) {
        if (query_boundary.get_query_params()->is_matching(*it)) {
            rows.push_back(*it);
        }
    }

    return rows;
}

const Boundary& KDVertex::get_boundary() const {
    return boundary_;
}
