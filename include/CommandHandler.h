#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include "User.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>
//#include <system>

using namespace std;

#define SUCCESS true
#define FAILURE false

class CommandHandler
{
public:
    static CommandHandler* getInstance();
    bool handleCreateNewFile(string filePath);
    bool handleCreateNewDirectory(string dirPath);
    bool handleDeleteDirectory(string dirPath);
    bool handleDeleteFile(string filePath);
    string handleGetCurrentDirectory();
private:
    CommandHandler();
    static CommandHandler* instance;
    vector<User*> users;
    User* loggedIn;

};

#endif
