#ifndef KDVERTICE_H
#define KDVERTICE_H

#include "boundary.hpp"
#include "query_boundary.hpp"
#include "../table_index/table_index_info.hpp"
#include "../../dump/dump_saver.hpp"
#include "search_tasks.hpp"

#include <set>

class SearchTask ;
class SearchTaskSearchNode ;

class KDVertex
{
public:
    explicit KDVertex(const TableIndexInfo& table_index_info, Boundary boundary);
    explicit KDVertex(const TableIndexInfo& table_index_info);

    void add_collection(std::vector<const Row*> rows);
    bool insert_row(const Row* row, int k);
    bool delete_row(const Row* row);
    std::vector<SearchTask*> search(const QueryBoundary& query_boundary) const;
    void clear();

    void dump_all_rows(DumpSaver& dump_saver) const;
    const Boundary& get_boundary() const;

    virtual ~KDVertex();
protected:
    void rebuild();

    Limiter find_good_limiter() const ;
    int calculate_limiter_efficiency(const Limiter& limit) const;

    std::vector<const Row*> linear_filter(const QueryBoundary& query_boundary) const;
    std::vector<const Row*> filter_non_index_conditions(const QueryBoundary& query_boundary) const ;
private:

    const TableIndexInfo& table_index_info_;

    // boundary of this vertex
    Boundary boundary_;

    // elements that are in this boundary
    std::vector<const Row*> rows_;

    // left and right subtree and divider
    int divider_property_number_;
    Type* divider_;
    KDVertex* left_;
    KDVertex* right_;
};

#endif // KDVERTICE_H
