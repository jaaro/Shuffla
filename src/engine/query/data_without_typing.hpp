#ifndef DATAWITHOUTTYPING_H
#define DATAWITHOUTTYPING_H

#include <string>
#include <vector>

#include "../table/table_definition.hpp"

class DataWithoutTyping
{
  public:
    DataWithoutTyping();
    virtual ~DataWithoutTyping();

    bool set(const std::string& request);
    std::string get_table_name() const ;
    std::vector<std::string> get_property_names() const ;
    std::string get_value_for_property(const std::string& property) const ;
    bool is_matching_table_definition(const TableDefinition& table_definition) const ;
  protected:
  private:
    std::string table_name;
    std::vector<std::string> property_names;
    std::vector<std::string> values;
};

#endif // DATAWITHOUTTYPING_H
