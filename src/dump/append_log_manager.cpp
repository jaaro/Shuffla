#include <iostream>

#include "append_log_manager.hpp"
#include "../config/config.hpp"

AppendLogManager::AppendLogManager()
{
  is_enabled = Config::getInstance().is_append_log_enabled;
}

AppendLogManager::~AppendLogManager()
{
  //dtor
}

void AppendLogManager::append(const Query* query) {
  if (is_enabled) {
    std::cout << "[Append log] " << query->to_string() << "\n";
  }
}
