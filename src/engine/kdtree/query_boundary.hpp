#ifndef QUERYBOUNDARY_H
#define QUERYBOUNDARY_H

#include "../query/search/query_parameters.hpp"

class QueryBoundary
{
    public:
        QueryBoundary(boost::shared_ptr<QueryParameters> query_params);
        virtual ~QueryBoundary();
    protected:
    private:
};

#endif // QUERYBOUNDARY_H
