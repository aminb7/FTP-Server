#ifndef USERMANAGER_H_
#define USERMANAGER_H_

#include "Configuration.h"
#include "UserIdentityInfo.h"
#include "User.h"

#include <vector>
#include <algorithm>

class UserManager
{
public:
    UserManager(Configuration configuration);

    ~UserManager();

    void add_user(int command_socket, int data_socket);
    void remove_user(int socket);

    User* get_user_by_socket(int socket);

    UserIdentityInfo* get_user_info_by_username(std::string username);

    void login_user(int user_socket, std::string username, std::string password);

    bool contains_as_special_file(std::string filename);

private:
    std::vector<UserIdentityInfo*> users_identity_info;
    std::vector<User*> users;

    std::vector<std::string> files;
};

#endif
