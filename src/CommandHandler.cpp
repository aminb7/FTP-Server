#include "CommandHandler.h"

using namespace std;

CommandHandler::CommandHandler(Configuration configuration) {
    user_manager = new UserManager(configuration.get_users());
}

vector<string> CommandHandler::do_command(int user_socket, char* command) {
    vector<string> command_parts = parse_command(command);

    if (command_parts[COMMAND] == USER_COMMAND)
        return handle_login_user(command_parts[ARG1]);

    else if (check_user_is_logged_in(user_socket) == false)
        return {"", ""};

    else if (command_parts[COMMAND] == PWD_COMMAND)
        return handle_get_current_directory();

    else if (command_parts[COMMAND] == MKD_COMMAND)
        return handle_create_new_directory(command_parts[ARG1]);

    else if (command_parts[COMMAND] == DELE_COMMAND && command_parts[ARG1] == DELE_DIRECTORY_OPTION)
        return handle_delete_directory(command_parts[ARG2]);

    else if (command_parts[COMMAND] == DELE_COMMAND && command_parts[ARG1] == DELE_FILE_OPTION)
        return handle_delete_file(command_parts[ARG2]);

    else if (command_parts[COMMAND] == LS_COMMAND) 
        return handle_get_list_of_files();

    else if (command_parts[COMMAND] == CWD_COMMAND)
        return handle_change_working_directory(command_parts[ARG1]);

    else if (command_parts[COMMAND] == RENAME_COMMAND)
        return handle_rename_file(command_parts[ARG1], command_parts[ARG2]);

    else if (command_parts[COMMAND] == RETR_COMMAND)
        return handle_download_file(command_parts[ARG1]);

    else if (command_parts[COMMAND] == HELP_COMMAND)
        return handle_help();

    else if (command_parts[COMMAND] == QUIT_COMMAND)
        return handle_logout_user(user_socket);

    else
        return {"", ""};
}

vector<std::string> CommandHandler::handle_login_user(string username) {
    return {"", ""};
}

vector<string> CommandHandler::handle_create_new_file(string file_path) {
    try {
        ofstream o(file_path);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return {"", ""};
    }

    return {"", ""};
}

vector<string> CommandHandler::handle_create_new_directory(string dir_path) {
    string bash_command = "mkdir " + dir_path;
    int status = system(bash_command.c_str());
    if (status == 0)
        return {"", ""};
    return {"", ""};
}

vector<string> CommandHandler::handle_delete_directory(string dir_path) {
    string bash_command = "rm -r " + dir_path;
    int status = system(bash_command.c_str());
    if (status == 0)
        return {"", ""};
    return {"", ""};
}

vector<string> CommandHandler::handle_delete_file(string file_path) {
    string bash_command = "rm " + file_path;
    int status = system(bash_command.c_str());
    if (status == 0)
        return {"", ""};
    return {"", ""};
}

//???
vector<string> CommandHandler::handle_get_current_directory() {
    system("pwd > file.txt");
    string result = read_file_to_string("file.txt");
    system("rm file.txt");
    return {"", ""};
}

vector<string> CommandHandler::handle_get_list_of_files() {
    system("ls > file.txt");
    string result = read_file_to_string("file.txt");
    system("rm file.txt");
    return {"", ""};
}

std::vector<std::string> CommandHandler::handle_change_working_directory(string dir_path) {
    return {"", ""};
}

std::vector<std::string> CommandHandler::handle_rename_file(string old_name, string new_name) {
    string bash_command = "mv " + old_name + " " + new_name;
    int status = system(bash_command.c_str());
    if (status == 0)
        return {"", ""};
    return {"", ""};
}

std::vector<std::string> CommandHandler::handle_download_file(string) {
    return {"", ""};
}

std::vector<std::string> CommandHandler::handle_help() {
    return {"", ""};
}

vector<string> CommandHandler::handle_logout_user(int user_socket) {
    user_manager->logout_user(user_socket);
    return {"", ""};
}

bool CommandHandler::check_user_is_logged_in(int user_socket) {
    return user_manager->is_logged_in(user_socket);
}