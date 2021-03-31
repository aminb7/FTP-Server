#ifndef USER_H_
#define USER_H_

#include "UserIdentityInfo.h"

#include <iostream>
#include <string>

#define ROOT ""

class User {
public:
    enum State {
        WAITING_FOR_USERNAME,
        WAITING_FOR_PASSWORD,
        LOGGED_IN,
    };

    User(int command_socket, int data_socket);

    int get_command_socket();
    int get_data_socket();
    State get_state();
    std::string get_username();
    std::string get_current_directory();
    UserIdentityInfo* get_user_identity_info();

    void set_state(State _state);
    void set_user_identity_info(UserIdentityInfo* _user_identity_info);
    void set_current_directory(std::string path);
    void decrease_available_size(double file_size);

    bool is_able_to_download(double file_size);
    bool is_able_to_access();

private:
    int command_socket;
    int data_socket;
    State state;
    std::string current_directory;
    UserIdentityInfo* user_identity_info;
};

#endif
