#include "kd_vertex.hpp"

KDVertex::KDVertex(const TableIndexInfo& table_index_info, Boundary boundary) : table_index_info_(table_index_info), boundary_(boundary)
{
    left_ = NULL;
    right_ = NULL;
}

KDVertex::KDVertex(const TableIndexInfo& table_index_info) : table_index_info_(table_index_info), boundary_(Boundary(table_index_info))
{
    left_ = NULL;
    right_ = NULL;
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
    rows_.insert(rows_.end(), rows.begin(), rows.end());
    rebuild();
}


bool KDVertex::insert_row(const Row* row, int k)
{
    if (!boundary_.is_point_inside(row)) return false;

    if (left_ == NULL) {
        rows_.push_back(row);
        rebuild();
        return true;
    }

    if (left_ != NULL) left_->insert_row(row, k+1);
    if (right_ != NULL) right_->insert_row(row, k+1);


    return true;
}

bool KDVertex::delete_row(const Row* row)
{
    if (!boundary_.is_point_inside(row)) return false;

    if (left_ == NULL) {
        for(size_t i=0; i<rows_.size(); i++) {
            if (rows_[i] == row) {
                rows_.erase(rows_.begin() + i);
            }
        }
    }

    if (left_ != NULL) left_->delete_row(row);
    if (right_ != NULL) right_->delete_row(row);
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

void KDVertex::rebuild()
{
    if (rows_.size() > 82 && left_ == NULL) {
        Limiter limit = find_good_limiter();

        Boundary left_boundary(boundary_);
        left_boundary.add_limiter(limit);
        Boundary right_boundary(boundary_);
        right_boundary.add_limiter(limit.createReverseLimiter());

        left_ = new KDVertex(table_index_info_, left_boundary);
        right_ = new KDVertex(table_index_info_, right_boundary);
        std::vector<const Row*> left_collection, right_collection;

        int property_index = limit.get_property_index();
        for(auto it = rows_.begin(); it !=rows_.end(); it++) {
            if (limit.is_value_matching((*it)->get_value(property_index))) {
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

Limiter KDVertex::find_good_limiter() const
{
    bool only_first = rand() % 2;

    std::vector<std::string> props = table_index_info_.get_table_definition()->get_property_names();
    std::vector<Limiter> limiters;

    for(auto it = rows_.begin(); it !=rows_.end(); it++) {
        for(int mask = 0; mask < 4; mask++) {
            if (rand() % (rows_.size() / 5 + 1) == 0) {
                std::string property = props[rand() % props.size()];
                if (only_first) property = props[0];
                int property_index = table_index_info_.get_table_definition()->get_property_index(property);

                limiters.push_back(Limiter(property_index, (*it)->get_value(property), mask/2, mask&1));
            }
        }
    }

    assert(limiters.size() > 0);

    int best_index = -1;
    int res = INT_MAX;
    for(std::size_t i=0; i<limiters.size(); i++) {
        int local_res = calculate_limiter_efficiency(limiters[i]);
        if (local_res < res) {
            best_index = i;
            res = local_res;
        }
        if (res <= signed(rows_.size()) / 8) {
            break;
        }
    }

    assert(best_index >= 0);

    return limiters[best_index];
}

int KDVertex::calculate_limiter_efficiency(const Limiter& limit) const
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
