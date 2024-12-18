#include "ServerSocket.hpp"
#include <iostream>
#include <unistd.h>


ServerSocket::ServerSocket(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("opening stream socket");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("binding stream socket");
    }

    if (listen(serverSocket, 5) < 0) {
        perror("listening stream socket");
    }

    std::cout << "Server is listening on port " << port << std::endl;
}

int ServerSocket::acceptConnection() {
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0) {
        perror("accept client connection");
        return -1;  // indicate failure
    }
    return clientSocket;
}

void ServerSocket::closeSocket() {
    if (serverSocket >= 0) {
        close(serverSocket);
        std::cout << "Socket closed." << std::endl;
        serverSocket = -1;
    }
}

ServerSocket::~ServerSocket() {
    closeSocket();
}
