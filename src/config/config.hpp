#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

/**
 * Class contains all config settings.
 *
 * It is a singleton.
 * Every class can request setting value by Config::getInstance().value
 *
 * You can set config values only by function Config::set
 * Use it only from ConfigLoader class.
 */


class Config
{
public:
    //DB CONFIG
    std::string host;
    std::string port;
    std::size_t number_of_threads;

    //DUMP
    bool is_append_log_enabled;
    std::string dump_file_name;

    //SLOW LOG
    bool is_slow_log_enabled;
    std::string slow_log_file_name;
    double slow_log_miliseconds_bound;
private:
    Config();
    Config(const Config&);
    void operator =(const Config&);
    virtual ~Config();
public:
    static Config& getInstance();
    void set(const std::string& name, const std::string& value);
};

#endif /* CONFIG_H_ */
