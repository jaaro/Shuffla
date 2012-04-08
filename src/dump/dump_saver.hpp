#ifndef DUMPSAVER_H
#define DUMPSAVER_H

#include <string>
#include <fstream>
#include <iostream>

class DumpSaver
{
public:
    DumpSaver();
    virtual ~DumpSaver();

    void append(const std::string& line);
protected:
private:
    std::ofstream* output;
};

#endif // DUMPSAVER_H
