#ifndef USER_H_
#define USER_H_

using namespace std;

#include <iostream>
#include <string>

class User
{
public:
    User(std::string _name, std::string _password, bool _is_admin, int _available_size);

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
