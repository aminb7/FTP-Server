#include "UserManager.h"

UserManager::UserManager(vector<User*> _users) {
    users = _users;
}

bool UserManager::is_logged_in(int user_socket) {
    if(std::find(sockets.begin(), sockets.end(), user_socket) != sockets.end())
        return true;
    return false;
}

void UserManager::login_user(int user_socket, string username, string password) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->is_matched_with(username, password)) {
            sockets.push_back(user_socket);
            break;
        }
    }
    
}

void UserManager::logout_user(int user_socket) {
    sockets.erase(std::remove(sockets.begin(), sockets.end(), user_socket), sockets.end());
}