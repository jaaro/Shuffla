#ifndef ROW_H
#define ROW_H

#include "../../engine/query/data_without_typing.hpp"
#include "../../engine/table/table_definition.hpp"
#include "../../engine/types/type.hpp"

class Row
{
public:
    explicit Row(const TableDefinition& table_definition, DumpLoader& dump_loader);
    explicit Row(const TableDefinition& table_definition, const DataWithoutTyping& data);
    virtual ~Row();

    Type* operator[] (const std::string& name) const ;
    std::string to_string() const ;
    std::string to_json() const ;

protected:
private:
    void add_value(const Type* type, const std::string& value);

private:
    const TableDefinition* table_definition;
    std::vector<Type*> values;
};

#endif // ROW_H
