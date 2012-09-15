#ifndef QUERYDROPTABLE_H
#define QUERYDROPTABLE_H

#include "../query.hpp"

class QueryDropTable : public Query
{
public:
    static const std::string HTTP_PREFIX;

    QueryDropTable();
    virtual ~QueryDropTable();

    virtual bool set(const std::string& request);
    virtual Query* parse(const std::string& request) const ;
    virtual bool is_modifying_data() const;
    std::string get_table_name() const;
protected:
private:
    std::string table_name;
};

#endif // QUERYDROPTABLE_H
