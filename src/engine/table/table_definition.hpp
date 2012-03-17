#ifndef TABLEDEFINITION_H
#define TABLEDEFINITION_H

#include <vector>
#include <string>

#include "../types/type.hpp"
#include "../types/types.hpp"
#include "../../dump/dump_loader.hpp"

class TableDefinition
{
public:
    TableDefinition();
    virtual ~TableDefinition();

    TableDefinition(const TableDefinition&);
    TableDefinition(DumpLoader& dump_loader);

    bool create_table_from_request(const std::string& request);
    std::string get_table_name() const ;

    std::vector<std::string> get_property_names() const ;
    bool is_correct_value_for_property(const std::string& property, const std::string& value) const ;

    const Type* get_property_type(const std::string& property) const ;
    std::string to_string() const ;
protected:
private:

    // returns true if adding property was successfull, false otherwise
    bool add_table_property(const Type* type, const std::string& name);

    std::string table_name;
    std::vector<std::string> property_names;
    std::vector<const Type*> property_types;

    Types types;
};

#endif // TABLEDEFINITION_H
