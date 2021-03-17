#include "Client.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

void Client::start(int server_port)
{
    /**
     * connect to server
     * loop on:
     *      receive input command.
     *      send to server.
     *      receive output of command from server.
     *      print output of command.
     */
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
        return;

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
        return;

    if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
        return;

    while (true)
    {
        cout << "> ";
        string command;
        cin >> command;
        send(client_fd, command.c_str(), command.size(), 0);
    }
}

int main()
{
    Client client;
    client.start(8080);
    return 0;
}