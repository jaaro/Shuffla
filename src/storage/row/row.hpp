#ifndef ROW_H
#define ROW_H

#include "../../engine/query/data_without_typing.hpp"
#include "../../engine/table/table_definition.hpp"

class Row
{
  public:
    Row(const TableDefinition& table_definition, const DataWithoutTyping& data);
    virtual ~Row();
  protected:
  private:
};

#endif // ROW_H
