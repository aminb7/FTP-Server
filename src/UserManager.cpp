#include "UserManager.h"

using namespace std;

UserManager::UserManager(Configuration configuration)
: users_identity_info(configuration.get_users_identity_info())
, files(configuration.get_files()) {
}
UserManager::~UserManager() {
    for (auto u : users_identity_info)
        delete u;
    users_identity_info.clear();

    for (auto u : users)
        delete u;
    users.clear();
}

void UserManager::add_user(int command_socket, int data_socket) {
    users.push_back(new User(command_socket, data_socket));
}

void UserManager::remove_user(int socket) {
    for(size_t i = 0; i < users.size(); ++i) {
        if (users[i]->get_command_socket() == socket) {
            users.erase(users.begin() + i);
            break;
        }
    }
}

User* UserManager::get_user_by_socket(int socket) {
    for(size_t i = 0; i < users.size(); ++i)
        if (users[i]->get_command_socket() == socket)
            return users[i];
    return nullptr;
}

UserIdentityInfo* UserManager::get_user_info_by_username(string username) {
    for(size_t i = 0; i < users_identity_info.size(); ++i)
        if (users_identity_info[i]->get_username() == username)
            return users_identity_info[i];
    return nullptr;
}

bool UserManager::is_logged_in(int) {
    // if(std::find(sockets.begin(), sockets.end(), user_socket) != sockets.end())
    //     return true;
    return false;
}

void UserManager::login_user(int, string username, string password) {
    for (size_t i = 0; i < users_identity_info.size(); i++) {
        if (users_identity_info[i]->is_matched_with(username, password)) {
            // sockets.push_back(user_socket);
            break;
        }
    }
}
