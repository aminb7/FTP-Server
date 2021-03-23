#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include "UserManager.h"
#include "Utilities.h"
#include "Configuration.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>

#define COMMAND 0
#define ARG1 1
#define ARG2 2

#define USER_COMMAND "user"
#define PWD_COMMAND "pwd"
#define MKD_COMMAND "mkd"
#define DELE_COMMAND "dele"
#define LS_COMMAND "ls"
#define CWD_COMMAND "cwd"
#define RENAME_COMMAND "rename"
#define RETR_COMMAND "retr"
#define HELP_COMMAND "help"
#define QUIT_COMMAND "quit"

#define DELE_DIRECTORY_OPTION "-d"
#define DELE_FILE_OPTION "-f"

class CommandHandler {
public:
    CommandHandler(Configuration configuration);

    std::vector<std::string> do_command(int user_socket, char* command);

    std::vector<std::string> handle_login_user(std::string username);
    std::vector<std::string> handle_create_new_file(std::string file_path);
    std::vector<std::string> handle_create_new_directory(std::string dir_path);
    std::vector<std::string> handle_delete_directory(std::string dir_path);
    std::vector<std::string> handle_delete_file(std::string file_path);
    std::vector<std::string> handle_get_current_directory();
    std::vector<std::string> handle_get_list_of_files();
    std::vector<std::string> handle_change_working_directory(string);
    std::vector<std::string> handle_rename_file(string old_name, string new_name);
    std::vector<std::string> handle_download_file(string);
    std::vector<std::string> handle_help();
    vector<std::string> handle_logout_user(int user_socket);

    bool check_user_is_logged_in(int user_socket);

private:
    //User* logged_in;
    UserManager* user_manager;
};

#endif
