#ifndef TYPE_H
#define TYPE_H

#include <string>

class Type
{
  public:
    Type();
    virtual ~Type();
    virtual std::string get_name() const = 0;
  protected:
  private:
};

#endif // TYPE_H
