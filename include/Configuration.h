#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <vector>

#include "User.h"

class Configuration
{
public:
    Configuration(const std::string path);

    int get_command_channel_port();
    int get_data_channel_port();
    std::vector<User> get_users();
    std::vector<std::string> get_files();

private:
    int command_channel_port;
    int data_channel_port;
    std::vector<User> users;
    std::vector<std::string> files;
};

#endif
