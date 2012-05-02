#include "query_boundary.hpp"

QueryBoundary::QueryBoundary(const TableIndexInfo& table_index_info, boost::shared_ptr<QueryParameters> query_params) : Boundary(table_index_info), query_params_(query_params) {

}

QueryBoundary::~QueryBoundary() {

}

boost::shared_ptr<QueryParameters> QueryBoundary::get_query_params() const {
    return query_params_;
}
