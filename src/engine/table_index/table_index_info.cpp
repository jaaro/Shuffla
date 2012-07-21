#include "table_index_info.hpp"
#include <sstream>
#include <cassert>

TableIndexInfo::TableIndexInfo(const TableDefinition* table_definition, const std::vector<std::string>& comparable_properties, const std::vector<std::string>& substring_properties)
    : table_definition_(table_definition)
{
    for(std::size_t i=0; i<comparable_properties.size(); i++) {
        comparable_properties_indexes_.push_back(table_definition_->get_property_index(comparable_properties[i]));
    }

    for(std::size_t i=0; i<substring_properties.size(); i++) {
        substring_properties_indexes_.push_back(table_definition_->get_property_index(substring_properties[i]));
    }
}

TableIndexInfo::TableIndexInfo(const TableDefinition* table_definition, DumpLoader& dump_loader)
    : table_definition_(table_definition)
{
    int size = dump_loader.get_next_int();
    while(size--) {
        comparable_properties_indexes_.push_back(dump_loader.get_next_int());
    }

    int size2 = dump_loader.get_next_int();
    while(size2--) {
        substring_properties_indexes_.push_back(dump_loader.get_next_int());
    }
}

TableIndexInfo::~TableIndexInfo()
{
    //dtor
}

const TableDefinition* TableIndexInfo::get_table_definition() const
{
    return table_definition_;
}

const std::string TableIndexInfo::to_string() const
{
    std::stringstream result;

    // adding comparable properties
    result << comparable_properties_indexes_.size() << " ";
    for(std::size_t i=0; i<comparable_properties_indexes_.size(); i++) {
        result << comparable_properties_indexes_[i] << " ";
    }
    result << "\n";

    // adding substring properties
    result << substring_properties_indexes_.size() << " ";
    for(std::size_t i=0; i<substring_properties_indexes_.size(); i++) {
        result << substring_properties_indexes_[i] << " ";
    }
    result << " ";

    return result.str();
}


int TableIndexInfo::get_property_index_limit() const
{
    return comparable_properties_indexes_.size();
}
int TableIndexInfo::get_boundary_index(int property_index) const
{
    for(int i=0; i<comparable_properties_indexes_.size(); i++) {
        if (comparable_properties_indexes_[i] == property_index) {
            return i;
        }
    }

    //TODO log error
    assert(0);
}
