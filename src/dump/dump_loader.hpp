#ifndef DUMPLOADER_H
#define DUMPLOADER_H

#include <string>
#include <iostream>
#include <fstream>

class DumpLoader
{
  public:
    DumpLoader();
    virtual ~DumpLoader();

    std::string get_line();
    int get_next_int();
    char get_next_char();
    std::string get_next_chars(const int size);


    bool is_eof();
    void close();

  protected:
  private:
    char* temp_buffor;
    std::ifstream* input;
};

#endif // DUMPLOADER_H
