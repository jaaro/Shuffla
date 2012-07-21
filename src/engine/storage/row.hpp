#ifndef ROW_H
#define ROW_H

#include <boost/property_tree/json_parser.hpp>

#include "../../engine/query/data_without_typing.hpp"
#include "../../engine/table/table_definition.hpp"
#include "../../engine/types/type.hpp"

/**
 * Representation of single row.
 */
class Row
{
public:
    explicit Row(const TableDefinition* table_definition, DumpLoader& dump_loader);
    explicit Row(const TableDefinition* table_definition, const DataWithoutTyping& data);
    virtual ~Row();

    Type* get_value(const std::string& name) const ;
    std::string to_string() const ;

    boost::property_tree::ptree get_property_tree() const;

protected:
private:
    void add_value(const Type* type, const std::string& value);

private:
    const TableDefinition* table_definition;
    std::vector<Type*> values;
};

#endif // ROW_H
