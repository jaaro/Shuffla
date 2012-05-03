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


bool KDVertice::insert_row(const Row* row, int k) {
    if (!boundary_.is_point_inside(row)) return false;
    if (contains_row(row)) return false;
    //std::cerr << "INSERT " << row << " " << k << "\n";
    rows_.insert(row);

    if (left_ == NULL) {
        rebuild();
        return true;
    }

    if (left_ != NULL) left_->insert_row(row, k+1);
    if (right_ != NULL) right_->insert_row(row, k+1);


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
    if (query_boundary.contains(boundary_)) {
        //if (!query_boundary.are_there_extra_requiremens()) return std::vector<const Row*>(rows_.begin(), rows_.end());
        return filter_non_index_conditions(query_boundary);
    }

    if (query_boundary.disjoint(boundary_)) {
        return std::vector<const Row*>();
    }

    if (left_ == NULL) return linear_filter(query_boundary);

    //std::cerr << "SEARCH " << &query_boundary << " " << boundary_.get_lower_bounds().size() + boundary_.get_upper_bounds().size() << "\n";
    std::vector<const Row*> result = left_->search(query_boundary);
    std::vector<const Row*> result2 = right_->search(query_boundary);
    result.insert(result.end(), result2.begin(), result2.end());

    return result;
}

void KDVertice::rebuild() {
    for(std::multiset<const Row*>::iterator it = rows_.begin(); it !=rows_.end(); it++) {
       assert(boundary_.is_point_inside(*it));
    }

    if (rows_.size() > 50 && left_ == NULL) {
        std::vector<std::string> props = table_index_info_.get_table_definition()->get_property_names();

        bool x, y;
        while(true) {
            random_shuffle(props.begin(), props.end());

            x = rand() % 2; y = rand() % 2;
            Limiter limit(props[0], (*(rows_.begin()))->get_value(props[0]), x, y);
            if (boundary_.is_good_limiter(limit)) {
                break;
            }
            /*std::cout << "FIGHTING! "<< props[0] << "\n";
            limit.debug();
            boundary_.debug();
            for(std::multiset<const Row*>::iterator it = rows_.begin(); it!=rows_.end(); it++) {
                std::cout << ((*it)->to_string()) << "\n";
            }*/
        }

        Limiter limit(props[0], (*(rows_.begin()))->get_value(props[0]), x, y);

        Boundary left_boundary(boundary_); left_boundary.add_limiter(limit);
        Boundary right_boundary(boundary_); right_boundary.add_limiter(limit.createReverseLimiter());

        left_ = new KDVertice(table_index_info_, left_boundary);
        right_ = new KDVertice(table_index_info_, right_boundary);
        std::vector<const Row*> left_collection, right_collection;

        for(std::multiset<const Row*>::iterator it = rows_.begin(); it !=rows_.end(); it++) {
            if (limit.is_value_matching((*it)->get_value(props[0]))) {
                left_collection.push_back(*it);
            } else {
                right_collection.push_back(*it);
            }
        }


        limit.debug();
        boundary_.debug();

        //std::cerr << left_collection[0]->get_value(props[0])->to_string() << "\n";
        //std::cerr << right_collection[0]->to_string() << "\n";
        //assert(0);

        std::cerr << "REBUILD " << left_collection.size() << " " << right_collection.size() << "\n";

        left_->add_collection(left_collection);
        right_->add_collection(right_collection);
    }
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
