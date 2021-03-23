#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <cstring>

using namespace std;

std::string read_file_to_string(std::string file_path);
vector<string> parse_command(char* input);

#endif