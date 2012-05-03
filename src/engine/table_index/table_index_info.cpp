#include "table_index_info.hpp"

TableIndexInfo::TableIndexInfo(const TableDefinition* table_definition, const std::vector<std::string>& index_properties) : table_definition_(table_definition), index_properties_(index_properties)
{
    //ctor
}

TableIndexInfo::~TableIndexInfo()
{
    //dtor
}

const TableDefinition* TableIndexInfo::get_table_definition() const {
    return table_definition_;
}
