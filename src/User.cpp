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
