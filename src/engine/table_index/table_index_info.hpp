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

    int get_property_index_limit() const ;
    int get_boundary_index(int property_index) const ;

protected:
private:
    const TableDefinition* table_definition_;
    std::vector<int> comparable_properties_indexes_;
    std::vector<int> substring_properties_indexes_;
};

#endif // TABLEINDEXINFO_H
