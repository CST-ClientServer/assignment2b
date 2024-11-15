//
// Created by carol on 2024-11-14.
//

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

class ServerSocket {
public:
    ServerSocket(int port);
    int acceptConnection();
    void closeSocket();

private:
    int serverSocket;
    struct sockaddr_in serverAddr{};
};



