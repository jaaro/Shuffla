#include "misc.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <cstdio>

Misc::Misc()
{
    //ctor
}

Misc::~Misc()
{
    //dtor
}



int Misc::string_to_int(const std::string& value)
{
    return boost::lexical_cast<int>( value );
}

std::string Misc::int_to_string(const int value)
{
    return boost::lexical_cast<std::string>( value );
}


double Misc::string_to_double(const std::string& value)
{
    return boost::lexical_cast<double>( value );
}


std::string Misc::double_to_string(const double value)
{
    return boost::lexical_cast<std::string>( value );
}


bool Misc::is_possible_property_name(const std::string& value)
{
    for(std::size_t i=0; i<value.size(); i++) {
        if (!isalnum(value[i]) && value[i] != '_') return false;
    }
    return value.size() > 0 && value != "ORDER_BY" && value != "LIMIT" && value != "OFFSET";
}


bool Misc::can_be_parsed_to_int(const std::string& value)
{
    try {
        boost::lexical_cast<int>( value );
        return true;
    } catch(std::exception e) {
        return false;
    }
}

bool Misc::can_be_parsed_to_double(const std::string& value)
{
    try {
        boost::lexical_cast<double>( value );
        return true;
    } catch(std::exception e) {
        return false;
    }
}

/**
 * I didn't know what library I should use to decode string
 * I found this source on: http://www.geekhideout.com/urlcode.shtml
 */

char Misc::from_hex(char ch) {
  return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

/* Converts an integer value to its hex character*/
char Misc::to_hex(char code) {
  static char hex[] = "0123456789abcdef";
  return hex[code & 15];
}

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char* Misc::url_encode(char *str) {
  char *pstr = str, *buf = (char*)malloc(strlen(str) * 3 + 1), *pbuf = buf;
  while (*pstr) {
    if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
      *pbuf++ = *pstr;
    else if (*pstr == ' ')
      *pbuf++ = '+';
    else
      *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}

/* Returns a url-decoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char* Misc::url_decode(char *str) {
  char *pstr = str, *buf = (char*)malloc(strlen(str) + 1), *pbuf = buf;
  while (*pstr) {
    if (*pstr == '%') {
      if (pstr[1] && pstr[2]) {
        *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
        pstr += 2;
      }
    } else if (*pstr == '+') {
      *pbuf++ = ' ';
    } else {
      *pbuf++ = *pstr;
    }
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}

/**
 * //TODO before release
 * This is horrible, find good library for that
 */

std::string Misc::url_encode(const std::string& decoded_string) {
    char* c_string = new char [decoded_string.size()+1];
    strcpy (c_string, decoded_string.c_str());
    char* result = Misc::url_encode(c_string);

    std::string ret = result;

    free(result);
    delete[] c_string;

    return ret;
}

std::string Misc::url_decode(const std::string& encoded_string) {
    char* c_string = new char [encoded_string.size()+1];
    strcpy (c_string, encoded_string.c_str());
    char* result = Misc::url_decode(c_string);

    std::string ret = result;

    free(result);
    delete[] c_string;

    return ret;
}


std::string Misc::format_current_time() {
    std::ostringstream msg;
    const boost::posix_time::ptime now =
      boost::posix_time::second_clock::local_time();

    boost::posix_time::time_facet*const f=
      new boost::posix_time::time_facet("%H:%M:%S");

    msg.imbue(std::locale(msg.getloc(),f));
    msg << now;
    return msg.str();
}


