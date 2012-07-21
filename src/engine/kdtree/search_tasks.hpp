#ifndef SEARCH_TASKS_H
#define SEARCH_TASKS_H

#include "kd_vertice.hpp"

class KDVertice;

class SearchTask {
    public:
        virtual ~SearchTask(){}
        virtual const Type* get_comparision_value(const std::string& property_name, bool is_order_descending) const = 0;
};

class SearchTaskFoundRow : public SearchTask {
    public:
        SearchTaskFoundRow(const Row* row);
        virtual ~SearchTaskFoundRow();
        virtual const Type* get_comparision_value(const std::string& property_name, bool is_order_descending) const ;
        const Row* get_row() const ;


    private:
        const Row* row_;
};

class SearchTaskSearchNode : public SearchTask {
    public:
        SearchTaskSearchNode(KDVertice* row);
        virtual ~SearchTaskSearchNode();
        virtual const Type* get_comparision_value(const std::string& property_name, bool is_order_descending) const ;

        KDVertice* get_vertice() const ;
    private:
        KDVertice* vertice_;
};

#endif // SEARCH_TASKS_H
