#ifndef SAVEDUMPMANAGER_H
#define SAVEDUMPMANAGER_H

#include <map>
#include <vector>

#include "boost/date_time/posix_time/posix_time.hpp"

/**
 * User can define: After x seconds, if there were y changes, than save db to dump.
 *
 * SaveDumpManager needs to be informed about all modifying queries.
 * This class answer question: Should I save dump now.
 */

class SaveDumpManager
{
public:
    typedef long long TIME_TYPE;

    void add_interval_save(const int period, const int changes);
    void notify_about_saving_dump();
    bool should_save_dump() ;
    void add_modifying_command();

    static SaveDumpManager& getInstance();

protected:

    TIME_TYPE get_current_second() const ;
    bool should_save_dump(const int period, const int changes) ;

private:

    long long counter;
    TIME_TYPE last_dump_save;
    std::map<TIME_TYPE, long long> modifing_commands_count;
    std::vector<std::pair<int, int> > periods;

    SaveDumpManager();

    virtual ~SaveDumpManager() {}
    SaveDumpManager(const SaveDumpManager&) {}
    void operator =(const SaveDumpManager&) {}

    boost::posix_time::ptime jan1st1970;
};

#endif // SAVEDUMPMANAGER_H
