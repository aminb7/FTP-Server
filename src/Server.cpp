#include "Server.h"
#include "Configuration.h"

#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

using namespace std;

Server::Server(Configuration configuration)
: command_channel_port(configuration.get_command_channel_port())
, data_channel_port(configuration.get_data_channel_port())
, users(configuration.get_users())
, files(configuration.get_files())
// command_handler(configuration.get_users())
{
}

void Server::start()
{
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
    while (true)
    {
        // Add sockets to set
        memcpy(&read_fds, &copy_fds, sizeof(copy_fds));

        // Select
        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0)
            return;

        int ready_sockets = activity;
        for (int i = 0; i <= max_fd  &&  ready_sockets > 0; ++i)
        {
            if (FD_ISSET(i, &read_fds))
            {

                // New connection.
                if (i == server_fd)
                {
                    int new_socket = accept(server_fd, NULL, NULL);
                    if (new_socket < 0)
                        return;

                    FD_SET(new_socket, &copy_fds);
                    if (new_socket > max_fd)
                        max_fd = new_socket;
                }
                // New readable socket.
                else
                {
                    bool close_connection = false;
                    memset(received_buffer, 0, sizeof received_buffer);
                    int result = recv(i, received_buffer, sizeof(received_buffer), 0);

                    if (result < 0)
                        if (errno != EWOULDBLOCK)
                            close_connection = true;

                    // Check to see if the connection has been closed by client.
                    if (result == 0)
                        close_connection = 1;

                    // Data is received.
                    if (result > 0)
                        cout << "received command: " << received_buffer << endl;

                    if (close_connection)
                    {
                        close(i);
                        FD_CLR(i, &copy_fds);
                        if (i == max_fd)
                            while (FD_ISSET(max_fd, &copy_fds) == 0)
                                max_fd -= 1;
                    }
                }
            }
        }

        printf("--------------------------------- EVENT ---------------------------------\n");
    }
}

int main()
{
    const string config_file_path = "configuration/config.json";
    Configuration configuration(config_file_path);
    Server server(configuration);
    server.start();
    return 0;
}
