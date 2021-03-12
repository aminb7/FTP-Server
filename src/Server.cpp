#include "Server.h"

Server::Server(Configuration configuration)
: users(configuration.get_users())
, command_handler(configuration.get_users())
{
}

void Server::start()
{
    /**
     * select.
     * call command_handler.handle ...
     */
}
