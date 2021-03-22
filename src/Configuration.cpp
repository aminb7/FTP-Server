#include "Configuration.h"

#include <iostream>
//#include <boostproperty_tree/ptree.hpp>                                        
#include <boost/property_tree/json_parser.hpp>

using namespace std;

Configuration::Configuration(const string path)
{
    namespace pt = boost::property_tree;

    pt::ptree root_tree;                                                    
    pt::read_json(path, root_tree);

    command_channel_port = root_tree.get_child("commandChannelPort").get_value<int>();
    data_channel_port = root_tree.get_child("dataChannelPort").get_value<int>();

    pt::ptree users_tree = root_tree.get_child("users");
    for (auto& item : users_tree.get_child(""))
    {
        string name = item.second.get<string>("user");
        string password = item.second.get<string>("password");
        bool is_admin = item.second.get<bool>("admin");
        int size = item.second.get<int>("size");
        
        users.push_back(User(name, password, is_admin, size));
    }

    pt::ptree files_tree = root_tree.get_child("files");
    for (auto& item : files_tree.get_child(""))
        files.push_back(item.second.get_value<string>());
}

int Configuration::get_command_channel_port()
{
    return command_channel_port;
}

int Configuration::get_data_channel_port()
{
    return data_channel_port;
}

std::vector<User> Configuration::get_users()
{
    return users;
}

std::vector<std::string> Configuration::get_files()
{
    return files;
}
