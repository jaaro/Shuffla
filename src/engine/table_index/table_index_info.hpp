#ifndef TABLEINDEXINFO_H
#define TABLEINDEXINFO_H

#include "../../dump/dump_saver.hpp"
#include "../table/table_definition.hpp"

class TableIndexInfo
{
    public:
        TableIndexInfo(const TableDefinition* table_definition, const std::vector<std::string>& index_properties, const std::vector<std::string>& substring_properties);
        TableIndexInfo(const TableDefinition* table_definition, DumpLoader& dump_loader);
        virtual ~TableIndexInfo();

        const TableDefinition* get_table_definition() const;
        const std::string to_string() const ;

    protected:
    private:
        const TableDefinition* table_definition_;
        std::vector<std::string> comparable_properties_;
        std::vector<std::string> substring_properties_;
};

#endif // TABLEINDEXINFO_H
