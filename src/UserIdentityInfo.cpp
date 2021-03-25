#include "UserIdentityInfo.h"

using namespace std;

UserIdentityInfo::UserIdentityInfo(string name, string password, bool is_admin, double available_size)
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

double UserIdentityInfo::get_available_size() {
    return available_size;
}

void UserIdentityInfo::decrease_available_size(double file_size) {
   available_size -= (file_size/1000);
}