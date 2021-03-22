#include "CommandHandler.h"

using namespace std;

vector<string> CommandHandler::do_command(char* command) {
    vector<string> command_parts = parse_command(command);
    if (command_parts[COMMAND] == PWD_COMMAND)
        return handle_get_current_directory();

    else if (command_parts[COMMAND] == MKD_COMMAND)
        return {"", ""};

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

    else
        return {"", ""};
}

vector<string> CommandHandler::parse_command(char* input) {
    vector<string> info;
    char *token = strtok(input, " "); 
   
    while (token != NULL) {
        info.push_back(token);
        token = strtok(NULL, " ");
    }
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

vector<string> CommandHandler::handle_get_current_directory() {
    //return logged_in->getCurrentDirectory();
    return {"", ""};
}

vector<string> CommandHandler::handle_get_list_of_files() {
    return {"", ""};
}

std::vector<std::string> CommandHandler::handle_change_working_directory(string) {
    return {"", ""};
}

std::vector<std::string> CommandHandler::handle_rename_file(string, string) {
    return {"", ""};
}

std::vector<std::string> CommandHandler::handle_download_file(string) {
    return {"", ""};
}

std::vector<std::string> CommandHandler::handle_help() {
    return {"", ""};
}
