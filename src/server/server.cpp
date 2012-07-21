#include <iostream>
#include <boost/thread/thread.hpp>

#include "../config/config.hpp"
#include "query_dispatcher.hpp"
#include "server.hpp"
#include "http/http_server.hpp"
#include "../dump/save_dump_manager.hpp"


Server::Server()
{
    // intensionally nothing
}

Server::~Server()
{
    // intensionally nothing
}

void Server::cron_function()
{
    while(true) {
        if (SaveDumpManager::getInstance().should_save_dump()) {
            SaveDumpManager::getInstance().notify_about_saving_dump();
            search_engine.save_dump();
        }
        boost::this_thread::sleep(boost::posix_time::seconds(5));
    }
}

void Server::start()
{
    try {
        DumpLoader dump_loader;
        search_engine = SearchEngine(dump_loader);
        QueryDispatcher query_dispatcher(&search_engine);

        boost::thread cron = boost::thread(&Server::cron_function, this);

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

