#ifndef CLIENT_H_
#define CLIENT_H_

#include "Configuration.h"

class Client {
public:
    Client() = default;

    void start(int command_channel_port, int data_channel_port);

private:
    static constexpr int MAX_COMMAND_LENGTH = 128;
};

#endif
