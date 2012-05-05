#include "dump_loader.hpp"
#include "../config/config.hpp"

DumpLoader::DumpLoader()
{
    temp_buffor = new char[5];
    input = new std::ifstream(Config::getInstance().dump_file_name.c_str() , std::ifstream::in );
}

DumpLoader::~DumpLoader()
{
    delete input;
    delete[] temp_buffor;
}


std::string DumpLoader::get_line()
{
    std::string line;
    std::getline(*input, line);
    return line;
}

bool DumpLoader::is_eof()
{
    return !input->good() || input->eof() || input->peek() == '\0';
}

int DumpLoader::get_next_int()
{
    int res;
    *input >> res;
    return res;
}

char DumpLoader::get_next_char()
{
    input->read(temp_buffor, 1);
    return temp_buffor[0];
}

std::string DumpLoader::get_next_chars(const int size)
{
    char ch;
    std::string res;

    for(int i=0; i<size; i++) {
        *input >> ch;
        res += ch;
    }

    return res;
}

std::string DumpLoader::get_next_string() {
    std::string res;
    *input >> res;

    return res;
}

void DumpLoader::close()
{
    input->close();
}

