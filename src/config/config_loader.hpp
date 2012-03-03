#ifndef CONFIGLOADER_H_
#define CONFIGLOADER_H_

#include <string>

class ConfigLoader
{
public:
    ConfigLoader();
    virtual ~ConfigLoader();

    void load_config(const std::string& path);

private:
    void parse_line_and_set_setting(const std::string& line);
};

#endif /* CONFIGLOADER_H_ */
