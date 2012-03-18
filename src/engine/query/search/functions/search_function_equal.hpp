#ifndef SEARCHFUNCTIONEQUAL_H
#define SEARCHFUNCTIONEQUAL_H

#include "search_function.hpp"

class SearchFunctionEqual : public SearchFunction
{
  public:
    SearchFunctionEqual();
    SearchFunctionEqual(const SearchFunctionEqual& fun);
    virtual ~SearchFunctionEqual();

    virtual bool set(const std::string& name);
    virtual bool set_value(const std::string& value);
    virtual std::string get_property_name() const;
    virtual bool is_available_for_type(const Type* type) const;
    virtual SearchFunction* clone() const ;

  protected:
  private:
  std::string property_name;
  std::string value;
};

#endif // SEARCHFUNCTIONEQUAL_H
