#include "table_index_info.hpp"
#include <sstream>

TableIndexInfo::TableIndexInfo(const TableDefinition* table_definition, const std::vector<std::string>& comparable_properties, const std::vector<std::string>& substring_properties)
    : table_definition_(table_definition), comparable_properties_(comparable_properties), substring_properties_(substring_properties)
{
    //ctor
}

TableIndexInfo::TableIndexInfo(const TableDefinition* table_definition, DumpLoader& dump_loader)
    : table_definition_(table_definition)
{
    int size = dump_loader.get_next_int();
    while(size--) {
        comparable_properties_.push_back(dump_loader.get_next_string());
    }

    int size2 = dump_loader.get_next_int();
    while(size2--) {
        substring_properties_.push_back(dump_loader.get_next_string());
    }
}

TableIndexInfo::~TableIndexInfo()
{
    //dtor
}

const TableDefinition* TableIndexInfo::get_table_definition() const {
    return table_definition_;
}

const std::string TableIndexInfo::to_string() const {
    std::stringstream result;

    // adding comparable properties
    result << comparable_properties_.size() << " ";
    for(std::size_t i=0; i<comparable_properties_.size(); i++) {
        result << comparable_properties_[i] << " ";
    }
    result << "\n";

    // adding substring properties
    result << substring_properties_.size() << " ";
    for(std::size_t i=0; i<substring_properties_.size(); i++) {
        result << substring_properties_[i] << " ";
    }
    result << " ";

    return result.str();
}
