#include <iostream>

#include "../config/config.hpp"
#include "query_dispatcher.hpp"
#include "server.hpp"
#include "http/http_server.hpp"

Server::Server()
{
    // intensionally nothing
}

Server::~Server()
{
    // intensionally nothing
}

void Server::start()
{
    try {
        DumpLoader dump_loader;
        SearchEngine search_engine(dump_loader);
        QueryDispatcher query_dispatcher(&search_engine);

        // loading server parameters
        std::string host = Config::getInstance().host;
        std::string port = Config::getInstance().port;
        int number_of_threads = Config::getInstance().number_of_threads;

        http::server2::http_server s(host, port, &query_dispatcher, number_of_threads);

        std::cout << "server started at " << host << " at port " << port << "\n";

        // Run the server until stopped.
        s.run();
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << "\n";
    }
}

