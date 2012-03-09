#ifndef TABLEDEFINITION_H
#define TABLEDEFINITION_H

#include <vector>
#include <string>

class TableDefinition
{
  public:
    enum Type {
        Integer,
        String
     };

    TableDefinition();
    virtual ~TableDefinition();

    bool create_table_from_request(const std::string& request);
    std::string get_table_name() const ;
    //bool is_valid_row(const Row& row) const;

    Type string_to_type(const std::string& type) const;

  protected:
  private:

    // returns true if adding property was successfull, false otherwise
    bool add_table_property(const Type& type, const std::string& name);

    std::string table_name;
    std::vector<std::string> property_name;
    std::vector<Type> property_type;
};

#endif // TABLEDEFINITION_H
