#ifndef DUMPPROCESSOR_H
#define DUMPPROCESSOR_H

#include <string>

class DumpProcessor
{
public:
    DumpProcessor();
    virtual ~DumpProcessor();

    void append(const std::string& line);
protected:
private:
};

#endif // DUMPPROCESSOR_H
