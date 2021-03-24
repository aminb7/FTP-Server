#include "Utilities.h"

using namespace std;

std::string read_file_to_string(std::string file_path) {
    std::ifstream t(file_path);
    std::string str;

    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}

vector<string> parse_command(char* input) {
    vector<string> info;
    char *token = strtok(input, " "); 
   
    while (token != NULL) {
        info.push_back(token);
        token = strtok(NULL, " ");
    }
    return info;
}

string create_message(int code, string message) {
    return to_string(code) + ": " + message;
}
