#include "dump_saver.hpp"
#include "../config/config.hpp"

#include <iostream>
#include <fstream>

DumpSaver::DumpSaver()
{
    output = new std::ofstream(Config::getInstance().dump_file_name.c_str());
}

DumpSaver::~DumpSaver()
{

    output->flush();
    output->close();
    delete output;
}

void DumpSaver::append(const std::string& line)
{
    *output << line;
}
