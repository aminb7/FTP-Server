#include "UserIdentityInfo.h"

using namespace std;

UserIdentityInfo::UserIdentityInfo(string name, string password, bool is_admin, int available_size)
: username(name)
, password(password)
, is_admin(is_admin)
, available_size(available_size) {
}

bool UserIdentityInfo::is_matched_with(string _username, string _password) {
    if (username == _username && password == _password)
        return true;
    return false;
}

std::string UserIdentityInfo::get_username() {
    return username;
}

std::string UserIdentityInfo::get_password() {
    return password;
}
