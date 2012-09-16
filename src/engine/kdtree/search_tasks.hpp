#ifndef SEARCH_TASKS_H
#define SEARCH_TASKS_H

#include "kd_vertex.hpp"

class KDVertex;

class SearchTask {
    public:
        virtual ~SearchTask(){}
        virtual const Type* get_comparison_value(int property_index, int boundary_index, bool is_order_descending) const = 0;
};

class SearchTaskFoundRow : public SearchTask {
    public:
        SearchTaskFoundRow(const Row* row);
        virtual ~SearchTaskFoundRow();
        virtual const Type* get_comparison_value(int property_index, int boundary_index, bool is_order_descending) const ;
        const Row* get_row() const ;


    private:
        const Row* row_;
};

class SearchTaskSearchNode : public SearchTask {
    public:
        SearchTaskSearchNode(KDVertex* row);
        virtual ~SearchTaskSearchNode();
        virtual const Type* get_comparison_value(int property_index, int boundary_index, bool is_order_descending) const ;

        KDVertex* get_vertex() const ;
    private:
        KDVertex* vertex_;
};

#endif // SEARCH_TASKS_H
