#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "../../include/config.h"
#include "../../include/config_loader.h"

ConfigLoader::ConfigLoader() {
	// intensionally nothing

}

ConfigLoader::~ConfigLoader() {
	// intensionally nothing
}


void ConfigLoader::load_config(const std::string& path) {
  std::ifstream input;
  input.open(path.c_str(), std::ios::in);

  if (!input) {
    std::cerr << "Can't open input file " << path << "\n";
  }

  std::string line;
  while(std::getline(input, line)) {
    if (line.size() > 5 && line[0] != '#') {
      //parsing name and value from given line
      int first_space_position = std::find(line.begin(), line.end(), ' ') - line.begin();
      std::string name = line.substr(0, first_space_position);
      std::string value = line.substr(first_space_position +1);

      //update Config
      Config::getInstance().set(name, value);
    }
  }

}
