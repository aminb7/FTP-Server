#ifndef SERVER_H_
#define SERVER_H_

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include "Configuration.h"
#include "CommandHandler.h"

class Server {
public:
    Server(Configuration configuration);

    ~Server();

    void start();

private:
    CommandHandler* command_handler;

    int command_channel_port;
    int data_channel_port;
};

#endif
