#include "dump_processor.hpp"
#include <iostream>

DumpProcessor::DumpProcessor()
{
    //ctor
}

DumpProcessor::~DumpProcessor()
{
    //dtor
}

void DumpProcessor::append(const std::string& line)
{
    std::cout << line << "\n";
}
