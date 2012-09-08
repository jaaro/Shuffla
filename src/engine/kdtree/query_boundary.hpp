#ifndef QUERYBOUNDARY_H
#define QUERYBOUNDARY_H

#include "boundary.hpp"
#include "../query/search/query_parameters.hpp"

class QueryBoundary : public Boundary
{
public:
    QueryBoundary(const TableIndexInfo& table_index_info, boost::shared_ptr<QueryParameters> query_params);

    boost::shared_ptr<QueryParameters> get_query_params() const ;
    bool are_there_extra_requiremens() const;
protected:
private:
    boost::shared_ptr<QueryParameters> query_params_;
    bool are_there_extra_requiremens_;
};

#endif // QUERYBOUNDARY_H
