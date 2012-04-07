#ifndef SERVER_H
#define SERVER_H


#include "../engine/search_engine.hpp"

class Server
{
public:
    Server();
    virtual ~Server();

    void cron_function() ;
    void start();
protected:
private:
SearchEngine search_engine;
};

#endif // SERVER_H
