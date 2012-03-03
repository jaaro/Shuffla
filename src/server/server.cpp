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
        // loading server parameters
        std::string host = Config::getInstance().host;
        std::string port = Config::getInstance().port;
        QueryDispatcher query_dispatcher;
        int number_of_threads = Config::getInstance().number_of_threads;

        http::server2::http_server s(host, port, query_dispatcher, number_of_threads);
        // Run the server until stopped.


        std::cout << "server started at " << host << " at port " << port << "\n";

        s.run();
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << "\n";
    }
}

