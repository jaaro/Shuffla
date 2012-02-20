#include <cstdio>
#include <string>
#include <boost/lexical_cast.hpp>

#include "../../include/config.h"

Config::Config() {
  //setting default values
  host = "0.0.0.0";
  port = "3000";

  number_of_threads = 16;
}

Config::~Config() {}
Config::Config(const Config&) {}
void Config::operator = (const Config&) {}

Config& Config::getInstance() {
  static Config instance;
  return instance;
};

void Config::set(const std::string& name, const std::string& value) {
  // setting config value
	if (name == "host") {
    host = value;
	} else if (name == "port") {
    port = value;
  } else if (name == "number_of_threads") {
      number_of_threads = boost::lexical_cast<int>(value);
  } else {
    printf("No such parameter as %s", name.c_str());
  }
}
