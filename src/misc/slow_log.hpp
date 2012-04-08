#ifndef SLOWLOG_H
#define SLOWLOG_H

#include <fstream>

/**
 * Slow log class.
 *
 * It is a singleton.
 * Every query that was executing longer than defined bound, will be logged by this class.
 */
class SlowLog
{
public:
    bool is_slow_log_enabled;
    double miliseconds_bound;
    std::string slow_log_file_name;
    std::fstream file;
private:
    SlowLog();
    SlowLog(const SlowLog&);
    void operator =(const SlowLog&);
    virtual ~SlowLog();
public:
    static SlowLog& getInstance();
    void log(const double miliseconds, const std::string& request);
};
#endif // SLOWLOG_H
