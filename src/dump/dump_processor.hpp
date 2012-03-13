#ifndef DUMPPROCESSOR_H
#define DUMPPROCESSOR_H

#include <string>
#include <fstream>
#include <iostream>

class DumpProcessor
{
public:
    DumpProcessor();
    virtual ~DumpProcessor();

    void append(const std::string& line);
protected:
private:
std::ofstream* output;
};

#endif // DUMPPROCESSOR_H
