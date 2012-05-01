#ifndef QUERYBOUNDARY_H
#define QUERYBOUNDARY_H

#include "boundary.hpp"
#include "../query/search/query_parameters.hpp"

class QueryBoundary : Boundary
{
    public:
        QueryBoundary(boost::shared_ptr<QueryParameters> query_params);
        virtual ~QueryBoundary();

        virtual bool contains(const Boundary& other_boundary) const ;
    protected:
    private:
};

#endif // QUERYBOUNDARY_H
