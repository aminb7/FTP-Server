#ifndef SERVER_H_
#define SERVER_H_

#include <vector>

#include "Configuration.h"

class Server
{
public:
    Server(Configuration configuration);

    void start();

private:
    // CommandHandler command_handler;

    int command_channel_port;
    int data_channel_port;
    std::vector<User> users;
    std::vector<std::string> files;
};

#endif
