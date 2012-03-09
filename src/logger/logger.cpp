#include <iostream>

#include "logger.hpp"

Logger::Logger(){}
Logger::~Logger() {}
Logger::Logger(const Logger&) {}
void Logger::operator = (const Logger&) {}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
};

void Logger::log_error(const std::string& message){ std::cout << "[Error] " << message << "\n"; }
void Logger::log_warning(const std::string& message){ std::cout << "[Warning] " << message << "\n"; }
void Logger::log_info(const std::string& message){ std::cout << "[Info] " << message << "\n"; }
void Logger::log_debug(const std::string& message){ std::cout << "[Debug] " << message << "\n"; }
