#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>

class User {
public:
    User(std::string name, std::string password, bool is_admin, int available_size);

    std::string get_name() {return name;}

private:
    std::string name;
    std::string password;
    bool is_admin;
    int available_size;
    std::string current_path;

    int command_channel_socket;
};

#endif
