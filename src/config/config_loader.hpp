#ifndef CONFIGLOADER_H_
#define CONFIGLOADER_H_

#include <string>

/**
 * ConfigLoader loads values to Config.
 *
 * It is done by load_config function which is executed only once, at the beginning.
 *
 *
 */
class ConfigLoader
{
public:
    ConfigLoader();
    virtual ~ConfigLoader();

    /**
     * @param path path to file that contains config.
     */
    void load_config(const std::string& path);

private:
    /**
     * It parses single line from config file.
     */
    void parse_line_and_set_setting(const std::string& line);
};

#endif /* CONFIGLOADER_H_ */
