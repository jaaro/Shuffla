#ifndef TABLEINDEX_H
#define TABLEINDEX_H

#include "table_index_info.hpp"
#include "../kdtree/kd_vertice.hpp"
#include "../../dump/dump_saver.hpp"

class TableIndex
{
    public:
        TableIndex(TableIndexInfo index_info);
        virtual ~TableIndex();

        std::vector<const Row*> search(boost::shared_ptr<QueryParameters> query_params) const ;
        void delete_row(const Row* row);
        void insert_row(const Row* row);
        void bulk_build(std::vector<const Row*> rows);
        void dump_all_rows(DumpSaver& dump_saver) const ;

    protected:
    private:
        const TableIndexInfo index_info_;
        KDVertice* kd_tree_;
};

#endif // TABLEINDEX_H
