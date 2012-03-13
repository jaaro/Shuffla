#include "dump_processor.hpp"
#include "../config/config.hpp"

#include <iostream>
#include <fstream>

DumpProcessor::DumpProcessor()
{
    output = new std::ofstream(Config::getInstance().dump_file_name.c_str());
}

DumpProcessor::~DumpProcessor()
{

    output->flush();
    output->close();
    delete output;
}

void DumpProcessor::append(const std::string& line)
{
    *output << line;
}
