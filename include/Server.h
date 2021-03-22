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

#define SUCCESS true
#define FAILURE false
#define COMMAND 0
#define ARG1 1
#define ARG2 2

class Server
{
public:
    Server(Configuration configuration);

    void start();
    void handleCreateNewDirectoryCommand(std::string dirPath);
    void handleDeleteDirectoryOrFileCommand(std::string option, std::string dirPath);
    std::vector<std::string> parseInput(char* input);

private:
    int command_channel_port;
    int data_channel_port;
    std::vector<User> users;
    std::vector<std::string> files;

};
#endif
