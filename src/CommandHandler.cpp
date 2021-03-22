#include "CommandHandler.h"

CommandHandler* CommandHandler::instance;

CommandHandler::CommandHandler()
{
    // Default Users for tests
    //users.push_back(new User("Sara", "1111"));
    //sers.push_back(new User("Negin", "2222"));
    //users.push_back(new User("Zahra", "3333"));
    //users.push_back(new User("Ghazal", "1234"));
}

CommandHandler* CommandHandler::getInstance()
{
	if (instance == NULL)
		instance = new CommandHandler();
	return instance;
}

bool CommandHandler::handleCreateNewFile(string filePath) {
    try {
        ofstream o(filePath);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return FAILURE;
    }
    
     return SUCCESS;
}

bool CommandHandler::handleCreateNewDirectory(string dirPath) {
    string bashCommand = "mkdir " + dirPath;
    int status = system(bashCommand.c_str());
    if (status == 0)
        return SUCCESS;
    return FAILURE;
}

bool CommandHandler::handleDeleteDirectory(string dirPath) {
    string bashCommand = "rm -r " + dirPath;
    int status = system(bashCommand.c_str());
    if (status == 0)
        return SUCCESS;
    return FAILURE;
}

bool CommandHandler::handleDeleteFile(string filePath) {
    string bashCommand = "rm " + filePath;
    int status = system(bashCommand.c_str());
    if (status == 0)
        return SUCCESS;
    return FAILURE;
}

string CommandHandler::handleGetCurrentDirectory() {
    //return loggedIn->getCurrentDirectory();
    return "nothing";
}
