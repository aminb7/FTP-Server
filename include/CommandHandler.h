#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include "User.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>

#define COMMAND 0
#define ARG1 1
#define ARG2 2

#define PWD_COMMAND "pwd"
#define MKD_COMMAND "mkd"
#define DELE_COMMAND "dele"
#define LS_COMMAND "ls"
#define CWD_COMMAND "cwd"
#define RENAME_COMMAND "rename"
#define RETR_COMMAND "retr"
#define HELP_COMMAND "help"

#define DELE_DIRECTORY_OPTION "-d"
#define DELE_FILE_OPTION "-f"

class CommandHandler {
public:
    CommandHandler() = default;

    std::vector<std::string> do_command(char* command);
    std::vector<std::string> parse_command(char* input);

    std::vector<std::string> handle_create_new_file(std::string filePath);
    std::vector<std::string> handle_create_new_directory(std::string dirPath);
    std::vector<std::string> handle_delete_directory(std::string dirPath);
    std::vector<std::string> handle_delete_file(std::string filePath);
    std::vector<std::string> handle_get_current_directory();
    std::vector<std::string> handle_get_list_of_files();
    std::vector<std::string> handle_change_working_directory(string);
    std::vector<std::string> handle_rename_file(string, string);
    std::vector<std::string> handle_download_file(string);
    std::vector<std::string> handle_help();

private:
    User* logged_in;
};

#endif
