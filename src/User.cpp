#include "User.h"

using namespace std;

User::User(int command_socket, int data_socket)
: command_socket(command_socket)
, data_socket(data_socket)
, state(WAITING_FOR_USERNAME)
, current_directory("")
, user_identity_info(nullptr) {
}

int User::get_command_socket() {
    return command_socket;
}

int User::get_data_socket() {
    return data_socket;
}

User::State User::get_state() {
    return state;
}

string User::get_username() {
    return user_identity_info->get_username();
}

string User::get_current_directory() {
    return current_directory;
}

UserIdentityInfo* User::get_user_identity_info() {
    return user_identity_info;
}

void User::set_state(User::State _state) {
    state = _state;
}

void User::set_user_identity_info(UserIdentityInfo* _user_identity_info) {
    user_identity_info = _user_identity_info;
}

void User::set_current_directory(string path) {
    current_directory = path;
}

bool User::is_able_to_download(double file_size) {
    if (user_identity_info->get_available_size() >= file_size)
        return true;
    return false;
}

void User::decrease_available_size(double file_size) {
   user_identity_info->decrease_available_size(file_size);
}