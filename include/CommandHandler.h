#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include "User.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>
//#include <system>

#define SUCCESS true
#define FAILURE false

class CommandHandler
{
public:
    static CommandHandler* getInstance();
    bool handleCreateNewFile(std::string filePath);
    bool handleCreateNewDirectory(std::string dirPath);
    bool handleDeleteDirectory(std::string dirPath);
    bool handleDeleteFile(std::string filePath);
    std::string handleGetCurrentDirectory();

private:
    CommandHandler();
    static CommandHandler* instance;
    std::vector<User*> users;
    User* loggedIn;

};

#endif
