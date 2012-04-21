#ifndef MISC_H
#define MISC_H

#include <string>

/**
 * Class with miscellaneous functions that are very simple,
 * but are used across whole project.
 */

class Misc
{
public:
    Misc();
    virtual ~Misc();

    static int string_to_int(const std::string& value);
    static double string_to_double(const std::string& value);

    static std::string int_to_string(const int value);
    static std::string double_to_string(const double value);

    static bool can_be_parsed_to_int(const std::string& value);
    static bool can_be_parsed_to_double(const std::string& value);

    static bool is_possible_property_name(const std::string& value);

    static std::string url_decode(const std::string& sSrc);
    static std::string url_encode(const std::string& sSrc);

    static char* url_encode(char *str);
    static char* url_decode(char *str);

    /* Converts a hex character to its integer value */
    static char from_hex(char ch);

    /* Converts an integer value to its hex character*/
    static char to_hex(char code);

    static std::string format_current_time();

protected:
private:
};

#endif // MISC_H
