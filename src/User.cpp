#include "User.h"

using namespace std;

User::User(string name, string password, bool is_admin, int available_size)
: name(name)
, password(password)
, is_admin(is_admin)
, available_size(available_size)
, current_path("")
, command_channel_socket(0) {
}

bool User::is_matched_with(string _username, string _password) {
    if (name == _username && password == _password)
        return true;
    return false;
}