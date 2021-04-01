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

bool UserManager::contains_as_special_file(string file_path) {
    size_t last_slash_pos = file_path.rfind(SLASH);
    string file_name = "";
    if (last_slash_pos == string::npos)
        file_name = file_path;
    else
        file_name = file_path.substr(last_slash_pos + 1);

    for (size_t i = 0; i < files.size(); i++)
        if (files[i] == file_name)
            return true;
    return false;
}
