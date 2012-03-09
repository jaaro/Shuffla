#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
  public:
    void log_error(const std::string& message);
    void log_warning(const std::string& message);
    void log_info(const std::string& message);
    void log_debug(const std::string& message);

private:
    Logger();
    Logger(const Logger&);
    void operator =(const Logger&);
    virtual ~Logger();
public:
    static Logger& getInstance();
};

#endif // LOGGER_H
