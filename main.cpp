#include <iostream>

#include "include/config_loader.h"
#include "include/server.h"

int main(int argc, char* argv[])
{
	if (argc == 2) {
    if (static_cast<std::string>(argv[1]) == "help" || argv[1][0] == '-') {
      std::cout << "Usage:\nshuffla [path to file with config]\n";
      return 1;
    }

    // loading config
    ConfigLoader configLoader;
    configLoader.load_config(argv[1]);
	}

	Server server;
	server.start();
}
