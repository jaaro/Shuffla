#ifndef TABLE_H
#define TABLE_H

#include "table_definition.hpp"

class Table
{
  public:
    Table();
    virtual ~Table();

    void set_table_definition(const TableDefinition& table_definition);
    std::string get_table_name() const ;

  protected:
  private:
    TableDefinition table_definition;

};

#endif // TABLE_H
