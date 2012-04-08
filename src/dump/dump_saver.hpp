#ifndef DUMPSAVER_H
#define DUMPSAVER_H

#include <string>
#include <fstream>
#include <iostream>

/**
 * Instance of this class should be provided to all classes that have something to save to dump.
 */
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
