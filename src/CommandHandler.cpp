#include "CommandHandler.h"

using namespace std;

CommandHandler::CommandHandler(Configuration configuration) {
    user_manager = new UserManager(configuration);
}

CommandHandler::~CommandHandler() {
    delete user_manager;
}

UserManager* CommandHandler::get_user_manager() {
    return user_manager;
}

vector<string> CommandHandler::do_command(int user_socket, char* command) {
    vector<string> command_parts = parse_command(command);

    User* user = user_manager->get_user_by_socket(user_socket);
    if (user == nullptr)
        return {"500: Error", ""};

    if (command_parts[COMMAND] == USER_COMMAND)
        return handle_username(command_parts[ARG1], user);

    else if (command_parts[COMMAND] == PASS_COMMAND)
        return handle_password(command_parts[ARG1], user);

    else if (user->get_state() != User::State::LOGGED_IN)
        return {"500: Error", ""};

    else if (command_parts[COMMAND] == PWD_COMMAND)
        return handle_get_current_directory(user);

    else if (command_parts[COMMAND] == MKD_COMMAND)
        return handle_create_new_directory(command_parts[ARG1], user);

    else if (command_parts[COMMAND] == DELE_COMMAND && command_parts[ARG1] == DELE_DIRECTORY_OPTION)
        return handle_delete_directory(command_parts[ARG2], user);

    else if (command_parts[COMMAND] == DELE_COMMAND && command_parts[ARG1] == DELE_FILE_OPTION)
        return handle_delete_file(command_parts[ARG2], user);

    else if (command_parts[COMMAND] == LS_COMMAND) 
        return handle_get_list_of_files(user);

    else if (command_parts[COMMAND] == CWD_COMMAND)
        return handle_change_working_directory(((command_parts.size() >= 2) ? command_parts[ARG1] : ""), user);

    else if (command_parts[COMMAND] == RENAME_COMMAND)
        return handle_rename_file(command_parts[ARG1], command_parts[ARG2], user);

    else if (command_parts[COMMAND] == RETR_COMMAND)
        return handle_download_file(command_parts[ARG1]);

    else if (command_parts[COMMAND] == HELP_COMMAND)
        return handle_help();

    else if (command_parts[COMMAND] == QUIT_COMMAND)
        return handle_logout(user);

    else
        return {"500: Error", ""};
}

vector<std::string> CommandHandler::handle_username(string username, User* user) {
    if(user->get_state() != User::State::WAITING_FOR_USERNAME)
        return {"503: Bad sequence of commands.", ""};

    UserIdentityInfo* user_identity_info = user_manager->get_user_info_by_username(username);

    if (user_identity_info == nullptr)
        return {"430: Invalid username or password.", ""};
    
    user->set_state(User::State::WAITING_FOR_PASSWORD);
    user->set_user_identity_info(user_identity_info);

    return {"331: User name Okay, need password.", ""};
}

vector<std::string> CommandHandler::handle_password(string password, User* user) {
    if(user->get_state() != User::State::WAITING_FOR_PASSWORD)
        return {"503: Bad sequence of commands.", ""};

    if (user->get_user_identity_info()->get_password() != password)
        return {"430: Invalid username or password.", ""};

    user->set_state(User::State::LOGGED_IN);

    return {"230: User looged in, proceed. Logged out if appropriate.", ""};
}

vector<string> CommandHandler::handle_get_current_directory(User* user) {
    string bash_command = "realpath " + user->get_current_directory() + " > file.txt";
    int status = system(bash_command.c_str());
    if (status != 0)
        return {"500: Error", ""};

    string result = read_file_to_string("file.txt");
    status = system("rm file.txt");
    if (status != 0)
        return {"500: Error", ""};

    return {"257: " + result, ""};
}

vector<string> CommandHandler::handle_create_new_directory(string dir_path, User* user) {
    string bash_command = "mkdir " + user->get_current_directory() + dir_path;
    int status = system(bash_command.c_str());
    if (status == 0)
        return {"257: " + dir_path + " created.", ""};
    return {"bad", ""};
}

vector<string> CommandHandler::handle_delete_directory(string dir_path, User* user) {
    string bash_command = "rm -r " + user->get_current_directory() + dir_path;
    int status = system(bash_command.c_str());
    if (status == 0)
        return {"250: " + dir_path + " deleted.", ""};
    return {"500: Error", ""};
}

vector<string> CommandHandler::handle_delete_file(string file_path, User* user) {
    string bash_command = "rm " + file_path;
    int status = system(bash_command.c_str());
    if (status == 0)
        return {"250: " + file_path + " deleted.", ""};
    return {"500: Error", ""};
}

vector<string> CommandHandler::handle_get_list_of_files(User* user) {
    string bash_command = "ls " + user->get_current_directory() + " > file.txt";
    int status = system(bash_command.c_str());
    if (status != 0)
        return {"500: Error", ""};

    string result = read_file_to_string("file.txt");
    status = system("rm file.txt");
    if (status != 0)
        return {"500: Error", ""};

    return {"226: List transfer done", result};
}

std::vector<std::string> CommandHandler::handle_change_working_directory(string dir_path, User* user) {
    if(dir_path == "")
        user->set_current_directory("");
    else
        user->set_current_directory(user->get_current_directory() + dir_path + "/");

    return {"250: Successful change.", ""};
}

std::vector<std::string> CommandHandler::handle_rename_file(string old_name, string new_name, User* user) {
    string bash_command = "mv " + user->get_current_directory() + old_name + " " +
            user->get_current_directory() + new_name;
    int status = system(bash_command.c_str());
    if (status == 0)
        return {"250: Successful change.", ""};
    return {"500: Error", ""};
}

std::vector<std::string> CommandHandler::handle_download_file(string) {
    return {"500: Error", ""};
}

std::vector<std::string> CommandHandler::handle_help() {
    string info = "214\n";
    info += USER_DESCRIPTION; 
    info += PASS_DESCRIPTION;
    info += PWD_DESCRIPTION;
    info += MKD_DESCRIPTION;
    info += DELE_DESCRIPTION;
    info += LS_DESCRIPTION;
    info += CWD_DESCRIPTION;
    info += RENAME_DESCRIPTION;
    info += RETR_DESCRIPTION;
    info += HELP_DESCRIPTION;
    info += QUIT_DESCRIPTION;
    return {info, ""};
    //return {"500: Error", ""};
}

vector<string> CommandHandler::handle_logout(User* user) {    
    if (user->get_state() != User::State::LOGGED_IN)
        return {"500: Error", ""};

    user->set_state(User::State::WAITING_FOR_USERNAME);

    return {"221: Successful Quit.", ""};
}
