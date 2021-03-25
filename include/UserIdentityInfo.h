#ifndef USERIDENTITYINFO_H_
#define USERIDENTITYINFO_H_

#include <iostream>
#include <string>

class UserIdentityInfo {
public:
    UserIdentityInfo(std::string name, std::string password, bool is_admin, double available_size);
    bool is_matched_with(std::string _username, std::string _password);
    void decrease_available_size(double file_size);

    std::string get_username();
    std::string get_password();
    double get_available_size();

private:
    std::string username;
    std::string password;
    bool is_admin;
    double available_size;
};

#endif
