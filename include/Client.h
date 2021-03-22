#ifndef CLIENT_H_
#define CLIENT_H_

class Client {
public:
    Client() = default;

    void start(int server_port);

private:
    static constexpr int MAX_COMMAND_LENGTH = 128;
};

#endif
