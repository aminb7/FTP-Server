#include "User.h"

using namespace std;

User::User(string _name, string _password, bool _is_admin, int _available_size)
: name(_name)
, password(_password)
, is_admin(_is_admin)
, available_size(_available_size)
, current_path("")
, command_channel_socket(0)
{
}

// User::User(string _username, string _password)
//     : username(_username), password(_password)
// {
//     currentDirectory = "";
// }

// string User::getCurrentDirectory() {
//     return currentDirectory;
// }