#include <iostream>

#include "src/config/config_loader.hpp"
#include "src/server/server.hpp"

void print_usage()
{
    std::cout << "Usage:\nshuffla [path to file with config]\n";
}

int main(int argc, char* argv[])
{
    if (argc > 2) {
        print_usage();
        return 1;
    }

    if (argc == 2) {
        if (static_cast<std::string>(argv[1]) == "help" || argv[1][0] == '-') {
            print_usage();
            return 1;
        }

        // loading config
        ConfigLoader configLoader;
        configLoader.load_config(argv[1]);
    }

    Server server;
    server.start();
}
