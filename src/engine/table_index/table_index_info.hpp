#ifndef TABLEINDEXINFO_H
#define TABLEINDEXINFO_H

#include "../../dump/dump_saver.hpp"
#include "../table/table_definition.hpp"

class TableIndexInfo
{
    public:
        TableIndexInfo(const TableDefinition* table_definition, const std::vector<std::string>& index_properties);
        virtual ~TableIndexInfo();

    protected:
    private:
        const TableDefinition* table_definition_;
        const std::vector<std::string> index_properties_;
};

#endif // TABLEINDEXINFO_H
