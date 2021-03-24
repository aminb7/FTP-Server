#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include "UserManager.h"
#include "Utilities.h"
#include "Configuration.h"
#include "User.h"
#include "UserIdentityInfo.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>

#define COMMAND 0
#define ARG1 1
#define ARG2 2

#define USER_COMMAND "user"
#define PASS_COMMAND "pass"
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

    ~CommandHandler();

    UserManager* get_user_manager();

    std::vector<std::string> do_command(int user_socket, char* command);

    std::vector<std::string> handle_username(std::string username, User* user);
    std::vector<std::string> handle_password(std::string password, User* user);
    std::vector<std::string> handle_get_current_directory(User* user);
    std::vector<std::string> handle_create_new_directory(std::string dir_path, User* user);
    std::vector<std::string> handle_delete_directory(std::string dir_path, User* user);
    std::vector<std::string> handle_delete_file(std::string file_path, User* user);
    std::vector<std::string> handle_get_list_of_files(User* user);
    std::vector<std::string> handle_change_working_directory(std::string dir_path, User* user);
    std::vector<std::string> handle_rename_file(std::string old_name, std::string new_name, User* user);
    std::vector<std::string> handle_download_file(std::string);
    std::vector<std::string> handle_help();
    std::vector<std::string> handle_logout(User* user);

private:
    //User* logged_in;
    UserManager* user_manager;
};

#endif
