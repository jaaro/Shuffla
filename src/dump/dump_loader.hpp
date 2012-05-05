#ifndef DUMPLOADER_H
#define DUMPLOADER_H

#include <string>
#include <iostream>
#include <fstream>

/**
 * DumpLoader, holds stream to file with dump.
 *
 * Instance of this class should be provided to all classes that were saving data into dump.
 */
class DumpLoader
{
public:
    DumpLoader();
    virtual ~DumpLoader();

    std::string get_line();
    int get_next_int();
    char get_next_char();
    std::string get_next_chars(const int size);
    std::string get_next_string();


    bool is_eof();
    void close();

protected:
private:
    char* temp_buffor;
    std::ifstream* input;
};

#endif // DUMPLOADER_H
