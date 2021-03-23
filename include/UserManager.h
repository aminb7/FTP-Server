#ifndef USERMANAGER_H_
#define USERMANAGER_H_

#include "User.h"

#include <vector>
#include <algorithm>

using namespace std;

class UserManager
{
public:
    UserManager(vector<User*> _users);
    bool is_logged_in(int user_socket);
    void login_user(int user_socket, string username, string password);
    void logout_user(int user_socket);
private:
    vector<User*> users;
    vector<int> sockets;
};

#endif