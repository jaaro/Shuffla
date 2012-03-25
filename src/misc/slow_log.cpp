#include <string>
#include <boost/lexical_cast.hpp>

#include "slow_log.hpp"
#include "../config/config.hpp"

SlowLog::SlowLog()
{
    is_slow_log_enabled = Config::getInstance().is_slow_log_enabled;
    slow_log_file_name = Config::getInstance().slow_log_file_name;
    miliseconds_bound = Config::getInstance().slow_log_miliseconds_bound;

    file.open (slow_log_file_name, std::fstream::out | std::fstream::app);
}

SlowLog::~SlowLog() {}
SlowLog::SlowLog(const SlowLog&) {}
void SlowLog::operator = (const SlowLog&) {}

SlowLog& SlowLog::getInstance()
{
    static SlowLog instance;
    return instance;
};

void SlowLog::log(const double miliseconds, const std::string& request)
{
    if (miliseconds >= miliseconds_bound) {
        file << "Slow query = " + request << " took " << miliseconds << " miliseconds\n";

        //since this is slow query, flushing shouldn't make much difference
        file.flush();
    }
}
