#ifndef KDVERTICE_H
#define KDVERTICE_H

#include "boundary.hpp"
#include "query_boundary.hpp"
#include "../table_index/table_index_info.hpp"
#include "../../dump/dump_saver.hpp"

#include <set>

class KDVertice
{
    public:
        explicit KDVertice(const TableIndexInfo* table_index_info, Boundary boundary, int depth);
        explicit KDVertice(const TableIndexInfo* table_index_info);

        void add_collection(std::vector<const Row*> rows);
        void insert_row(const Row* row);
        void delete_row(const Row* row);
        std::vector<const Row*>  search(const QueryBoundary& boundary) const;
        void clear();

        void dump_all_rows(DumpSaver& dump_saver) const;

        virtual ~KDVertice();
    protected:
        void rebuild();
    private:
        Boundary boundary;
        std::set<const Row*> rows;
};

#endif // KDVERTICE_H
