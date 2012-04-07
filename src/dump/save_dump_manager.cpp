#include "save_dump_manager.hpp"
#include "time.h"

#include <boost/date_time/gregorian/gregorian.hpp>

SaveDumpManager::SaveDumpManager()
{
    counter = 0;
    last_dump_save = -1;
    jan1st1970 = boost::posix_time::ptime(boost::gregorian::date(1970, 1, 1));
}

void SaveDumpManager::add_interval_save(const int period, const int changes)
{
    periods.push_back(std::make_pair(period, changes));
}

void SaveDumpManager::notify_about_saving_dump()
{
    last_dump_save = get_current_second();
    modifing_commands_count[-get_current_second()] = counter;
}

bool SaveDumpManager::should_save_dump()
{
    for(std::size_t i = 0; i < periods.size(); i++) {
        if (should_save_dump(periods[i].first, periods[i].second)) {
            return true;
        }
    }

    return false;
}

void SaveDumpManager::add_modifying_command()
{
    modifing_commands_count[-get_current_second()] = counter++;
}

SaveDumpManager::TIME_TYPE SaveDumpManager::get_current_second() const
{
    boost::posix_time::ptime now(boost::posix_time::second_clock::local_time());
    return (now - jan1st1970).total_seconds();
}


bool SaveDumpManager::should_save_dump(const int period, const int changes)
{
   SaveDumpManager::TIME_TYPE current_second = get_current_second();
   if (current_second - last_dump_save < period) return false;

   std::map<SaveDumpManager::TIME_TYPE, long long>::iterator it = modifing_commands_count.upper_bound(-current_second + period);
   if (it == modifing_commands_count.end()) return false;

   return counter - it->second >= changes;

}

SaveDumpManager& SaveDumpManager::getInstance()
{
    static SaveDumpManager instance;
    return instance;
};
