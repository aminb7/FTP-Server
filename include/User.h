#ifndef USER_H_
#define USER_H_

#include "UserIdentityInfo.h"

#include <iostream>
#include <string>

class User {
public:
    enum State {
        WAITING_FOR_USERNAME,
        WAITING_FOR_PASSWORD,
        LOGGED_IN,
    };

    User(int socket);

    int get_socket();
    State get_state();
    std::string get_current_directory();
    UserIdentityInfo* get_user_identity_info();

    void set_state(State _state);
    void set_user_identity_info(UserIdentityInfo* _user_identity_info);
    void set_current_directory(std::string path);

private:
    int socket;
    State state;
    std::string current_directory;
    UserIdentityInfo* user_identity_info;
};

#endif
