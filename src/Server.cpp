#include "Server.h"
#include "Configuration.h"

using namespace std;

Server::Server(Configuration configuration)
: command_channel_port(configuration.get_command_channel_port())
, data_channel_port(configuration.get_data_channel_port()) {
    logger = new Logger(LOG_FILE);
    command_handler = new CommandHandler(configuration, logger);
}

Server::~Server() {
    delete command_handler;
}

void Server::start() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        return;

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return;

    struct sockaddr_in address;
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
        return;

    constexpr int backlog = 10;
    if (listen(server_fd, backlog) < 0)
        return;

    fd_set read_fds, copy_fds;
    FD_ZERO(&copy_fds);
    FD_SET(server_fd, &copy_fds);
    int max_fd = server_fd;
    int activity;
    char received_buffer[128] = {0};

    printf("server is starting ...\n");
    while (true) {
        // Add sockets to set
        memcpy(&read_fds, &copy_fds, sizeof(copy_fds));

        // Select
        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0)
            return;

        int ready_sockets = activity;
        for (int fd = 0; fd <= max_fd  &&  ready_sockets > 0; ++fd) {
            if (FD_ISSET(fd, &read_fds)) {
                // New connection.
                if (fd == server_fd) {
                    int new_command_socket = accept(server_fd, NULL, NULL);
                    if (new_command_socket < 0)
                        return;

                    int new_data_socket = accept(server_fd, NULL, NULL);
                    if (new_data_socket < 0)
                        return;
                    
                    command_handler->get_user_manager()->add_user(new_command_socket, new_data_socket);
                    FD_SET(new_command_socket, &copy_fds);
                    if (new_command_socket > max_fd)
                        max_fd = new_command_socket;
                }

                // New readable socket.
                else {
                    bool close_connection = false;
                    memset(received_buffer, 0, sizeof received_buffer);
                    int result = recv(fd, received_buffer, sizeof(received_buffer), 0);

                    if (result < 0)
                        if (errno != EWOULDBLOCK)
                            close_connection = true;

                    // Check to see if the connection has been closed by client.
                    if (result == 0)
                        close_connection = 1;

                    // Data is received.
                    if (result > 0) {
                        cout << "received command: " << received_buffer << endl;
                        vector<string> output = command_handler->do_command(fd, received_buffer);
                        cout << "Command output: " << output[0] << endl;
                        cout << "Data output: " << output[1] << endl;

                        send(fd , output[0].c_str() , output[0].size() , 0);
                        send(command_handler->get_user_manager()->get_user_by_socket(fd)->get_data_socket(),
                                output[1].c_str() , output[1].size() , 0);
                    }

                    if (close_connection) {
                        close(fd);
                        close(command_handler->get_user_manager()->get_user_by_socket(fd)->get_data_socket());
                        command_handler->get_user_manager()->remove_user(fd);
                        FD_CLR(fd, &copy_fds);
                        if (fd == max_fd)
                            while (FD_ISSET(max_fd, &copy_fds) == 0)
                                max_fd -= 1;
                    }
                }
            }
        }

        printf("--------------------------------- EVENT ---------------------------------\n");
    }
}

int main() {
    const string config_file_path = "configuration/config.json";
    Configuration configuration(config_file_path);
    Server server(configuration);
    server.start();
    return 0;
}
